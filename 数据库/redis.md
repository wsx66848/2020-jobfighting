# redis

## 事务

  * MULTI EXEC DISCARD用来显式开启并控制事务
  WATCH 解决事务并发产生的不可重复度和幻读
  * 事务在调用EXEC之前所有命令都会被序列化并加入队列，不执行任何command，在EXEC命令调用后所有command都被执行，或者调用discard命令，所有command都被忽略
  * redis使用AOF 使用额外的write操作将事务写入磁盘，用来宕机时的恢复
  * 事务中的错误有两种，一种是调用EXEC命令之前的错误，这种一般是命令语法错误(INCR a b c)，对这种错误的处理在redis2.6.5之前，客户端仍可以调用exec命令使得事务执行，只不过错误的命令不执行；在redis2.6.5之后，服务端会记住在EXEC调用之前的错误，当客户端调用EXEC时，服务端会拒绝执行事务并返回错误，同时自动清除命令队列
  * 事务中的错误是在调用EXEC命令之后出现，即使用错误的命令对某个key操作（比如对字符串执行了列表的操作 LPOP str） 此时服务端在执行命令时，只有错误命令执行失败并返回错误信息，其他命令不影响执行
  * 事务不支持回滚，DISCARD会清除命令队列并恢复到正常连接状态

## 字符串

简单动态字符串 Sds(Simple Dynamic String) 是redis底层所使用的字符串表示

### 用途

redis是基于key-val的 val可以是多种类型，但是key都是字符串，所以redis中的字符串有两种用途
1. 实现字符串对象（StringObject）
2. 在Redis程序内部用作char*类型的替代品

### 起因

redis是用C语言实现的单进程单线程的程序，char* 是C语言中的字符串表示方式，之所以不使用char*而使用Sds，主要原因在于两点

1. char\*功能单一，不能高效支持在Redis中常见的字符串追加和长度计算操作，char\*在计算长度时时间复杂度是O(N), 对字符串N次追加，需要对字符串进行N次内存重分配(realloc) redis中的STRLEN和APPEND这两个简单常用的操作不应该成为redis性能的瓶颈
2. redis除了C字符串之外，还要处理协议内容、字节数组，所以redis中的字符串还应该是二进制安全的: 程序不应对字符串里面保存的数据做任何假设， 数据可以是以 \0 结尾的 C 字符串， 也可以是单纯的字节数组， 或者其他格式的数据

redis的Sds既可以实现高效地长度计算和追加，同时是二进制安全的

### 实现方式
``` c
typedef char* sds;
struct sdshdr {
  int len // 已占用长度
  int free // 剩余可用长度
  char buf[] //实际保存字符串的地方
}
```
len属性可以实现复杂度为O（1）的长度计算操作，同时所有处理sdshdr的函数都必须正确地跟新len和free

#### 追加优化

在append时操作时减少内存重分配的次数，如果当前剩余长度free 大于等于 需要附加字符串的长度，则不再进行空间分配  
否则 新字符串的长度等于当前字符串长度len+附加字符串的长度，如果新长度小于1M，那么为字符串分配2倍于新长度的空间  
如果大于1M，则为字符串额外分配1M的空间。之后分配内存并更新free属性
``` python
def sdsMakeRoomFor(sdshdr, required_len):

    # 预分配空间足够，无须再进行空间分配
    if (sdshdr.free >= required_len):
        return sdshdr

    # 计算新字符串的总长度
    newlen = sdshdr.len + required_len

    # 如果新字符串的总长度小于 SDS_MAX_PREALLOC
    # 那么为字符串分配 2 倍于所需长度的空间
    # 否则就分配所需长度加上 SDS_MAX_PREALLOC 数量的空间
    if newlen < SDS_MAX_PREALLOC:
        newlen *= 2
    else:
        newlen += SDS_MAX_PREALLOC

    # 分配内存
    newsh = zrelloc(sdshdr, sizeof(struct sdshdr)+newlen+1)

    # 更新 free 属性
    newsh.free = newlen - sdshdr.len

    # 返回
    return newsh
```
这样做的代价是额外分配的内存有可能会浪费，因为它只有在key-value对被删除时 或者 redis重启时 才会被释放。因为执行 APPEND 命令的字符串键数量通常并不多， 占用内存的体积通常也不大， 所以这一般并不算什么问题。另一方面， 如果执行 APPEND 操作的键很多， 而字符串的体积又很大的话， 那可能就需要修改 Redis 服务器， 让它定时释放一些字符串键的预分配空间， 从而更有效地使用内存。

### 数据分片

redis的数据的水平切分不是用一致性哈希来实现的，而是用虚拟哈希槽机制实现的  slot = CRC16(key) & 16383
Redis Cluster采用虚拟哈希槽分区  
* 解耦数据和节点之间的关系，简化了节点扩容和收缩难度
* 节点自身维护槽的映射关系，不需要客户端或者代理服务器维护槽分区元数据
* 支持节点、槽和键之间的映射查询，用于数据路由，在线集群伸缩等场景
  
1. 扩容集群
   当一个新节点加入现有集群后，需要制定槽的迁移计划，进行槽和数据的迁移，来确保每个节点负责相似数量的槽
    1. 新节点M4加入并成为主节点，此时没有负责的槽，所以不能接受任何读写操作
    2. 对 M4 节点发送 cluster setslot { slot } importing { sourceNodeId} 命令，让目标节点准备导入槽的数据
    3. 对源节点，也就是 M1，M2，M3 节点发送 cluster setslot { slot } migrating { targetNodeId} 命令，让源节点准备迁出槽的数据
    4. 源节点执行 cluster getkeysinslot { slot } { count } 命令，获取 count 个属于槽 { slot } 的键，然后执行步骤六的操作进行迁移键值数据
    5. 在源节点上执行 migrate { targetNodeIp} " " 0 { timeout } keys { key... } 命令，把获取的键通过 pipeline 机制批量迁移到目标节点，批量迁移版本的 migrate 命令在 Redis 3.0.6 以上版本提供
    6. 重复执行步骤 4 和步骤 5 直到槽下所有的键值数据迁移到目标节点
    7. 向集群内所有主节点发送 cluster setslot { slot } node { targetNodeId } 命令，通知槽分配给目标节点。为了保证槽节点映射变更及时传播，需要遍历发送给所有主节点更新被迁移的槽所在新节点
2. 收缩集群
    1. 首先需要确认下线节点是否有负责的槽，如果是，需要把槽迁移到其他节点，保证节点下线后整个集群槽节点映射的完整性。
    2. 当下线节点不再负责槽或者本身是从节点时，就可以通知集群内其他节点忘记下线节点，当所有的节点忘记改节点后可以正常关闭（ cluster forget { downNodeId }）
3. 客户端路由
   1. 当redis节点接到任何键相关命令时首先计算键对应的槽，根据槽找到对应节点，如果是自身就处理命令，如果不是自身就发送MOVED重定向错误
   2. Smart客户端会在内部维护slot与节点的映射关系，实现本地的key到节点的查询，从而保证IO效率最大化，而MOVED重定向负责协助客户端更新映射关系
   3. 当redis集群进行在线迁移槽和数据时，某些slot的数据可能会出现一部分数据在源节点，另一部分在目标节点，此时客户端的键命令流程如下
      * 客户端根据本地 slot 缓存发送命令到源节点，如果存在键对应则直接执行并返回结果给客户端。
      * 如果节点返回 MOVED 错误，更新本地的 slot 到 Redis 节点的映射关系，然后重新发起请求。
      * 如果数据正在迁移中，节点会回复 ASK 重定向异常。格式如下: ( error ) ASK { slot } { targetIP } : {targetPort}
      客户端从 ASK 重定向异常提取出目标节点信息，发送 asking 命令到目标节点打开客户端连接标识，再执行键命令  

ASK 和 MOVED 虽然都是对客户端的重定向控制，但是有着本质区别。ASK 重定向说明集群正在进行 slot 数据迁移，客户端无法知道什么时候迁移完成，因此只能是临时性的重定向，客户端不会更新 slot 到 Redis 节点的映射缓存。但是 MOVED 重定向说明键对应的槽已经明确指定到新的节点，因此需要更新 slot 到 Redis 节点的映射缓存 
 
4. 故障转移  
   默认情况下，当集群 16384 个槽任何一个没有指派到节点时整个集群不可用。执行任何键命令返回 CLUSTERDOWN Hash slot not served 命令。当持有槽的主节点下线时，从故障发现到自动完成转移期间整个集群是不可用状态，对于大多数业务无法忍受这情况，因此建议将参数 cluster-require-full-coverage 配置为 no ，当主节点故障时只影响它负责槽的相关命令执行，不会影响其他主节点的可用性

## 热key和大key问题

1. 热key问题

突然并发的几十万qps去访问redis上的某个特定key,流量过于集中达到物理网卡上限，导致这台redis服务器宕机。接下来这个key请求机会直接去查询数据库，导致服务不可用

### 如何发现
    1. 业务经验   
      比如商品描述，那个商品的key，比如某明星结婚，那个明星的key
    2. 在客户端收集  
      在客户端操作redis前，加入一行代码进行数据统计，然后向外部发送通知消息，缺点是会对客户端代码造成入侵，以及key较多时客户端有内存泄漏的风险，给客户端程序带来负担
    3. 在proxy层收集  
      在redis节点前添加反向代理，反向代理是统一的入口，在反向代理处统计，然后上报。缺点是增加了redis集群架构的复杂度
    4. 用redis自带命令
      * monitor命令 该命令可以实时抓取出redis服务器接收到的命令，然后写代码统计热key,或者用分析工具redis-faina。但是这种方式比较占用内存，在高并发条件下有内存暴增的风险
      * hotkeys redis4.0.3提供了redis-cli的热点key发现功能-hotkeys。如果key比较多，执行起来会比较慢。实现是通过利用LFU属性完成对热点key的统计（缓存淘汰策略maxmemory-policy需是LFU相关）
    5. 抓包评估
      redis客户端使用TCP协议，通信协议采用RESP。自己写程序监听端口，按RESP协议解析包

### 如何解决

    1.  利用二级缓存
      ehcache 或者 hashmap。发现热key之后，把热key加载到系统的JVM中，针对热Key请求，直接从JVM中获取，不会走到redis层
    2. 备份热key
      把热key在多个节点上做备份，对读请求负载均衡
``` go
const M = N * 2
//生成随机数
random = GenRandom(0, M)
//构造备份新key
bakHotKey = hotKey + “_” + random
data = redis.GET(bakHotKey)
if data == NULL {
    data = GetFromDB()
    redis.SET(bakHotKey, expireTime + GenRandom(0,5))
}
```
随机值是为了确保更改key的hash值，从而落到不同的slot中，这样可以从不同的redis节点去获取

2. 大key问题
   ### 定义
   大key问题就是key本身的值比较大，或者key所对应的map list set比较大
   ### 场景
      1. 热门话题下评论、答案排序
      2. 大V的粉丝列表
      3. 使用不恰当，或者对业务预估不准确、不及时进行处理垃圾数据等
    ### 问题
    redis是单线程模式，大key会带来一些问题
      1. 集群模式在slot分片均匀情况下，会出现数据和查询倾斜情况，部分有大key的Redis节点占用内存多，QPS高
      2. 大key相关的删除或者自动过期时，会出现qps突降或者突升的情况，极端情况下，会造成主从复制异常，Redis服务阻塞无法响应请求。大key的体积与删除耗时可参考下表：
            key类型 field数量耗时  
            Hash~100万~1000ms  
            List~100万~1000m  
            Set~100万~1000ms  
            Sorted Set~100万~1000ms  
    ### 如何发现
      1. redis-rdb-tools工具
         先在客户端中执行命令bgsave生成rdb(快照文件) 然后rdb -c memory dump.rdb 输出的信息包含数据类型，key名称，内存大小，编码类型，包含元素个数，其中最长的元素长度，缺点是离线操作，获取结果时间较长
      2. redis-cli --bigkeys命令
         对整个redis扫描，寻找较大的key。显示扫描进度和最终的结果，每种类型的最大值以及每种类型的统计信息。优点在于在线扫描不阻塞服务，缺点是信息较少，内容不精确，只有string类型是以字节长度为衡量标准，其余类型都是以元素个数，但元素个数多不一定占用内存多
      3. 自定义python扫描脚本
         编写脚本 通过strlen hlen scard命令获取字节大小和元素个数
         
    ### 如何解决
       * redis 4.0之前
           1. 将大key附加某一维度的信息继续拆分，将一个大key分为多个小key
           2. 获取到大key之后，通过hscan(扫描哈希表) sscan(扫描列表) zscan(扫描集合) 方式渐进删除若干个元素，这种方法对自动过期的key无能为力
       * redis4.0之后
           1. memory usage 内存维度的抽样算法  
              这个方法就是抽样法，例如一个hashmap长度为L，从L中随机抽出N个field，以这N个field的平均内存使用量作为整个map的平均内存量，然后乘以field数量L作为hashmap的总体内存使用率。抽样数量N决定了内存大小的准确性和计算成本
           2. lazyfree 异步删除优化
              Lazyfree的原理是在删除的时候只进行逻辑删除，把满足阈值的大key释放操作放入BIO_LAZY_FREE后台线程任务队列去处理，减少删除大key对redis主线程的阻塞，有效地避免因删除大key带来的性能问题。Redis的单线程是指redis的网络请求模块使用了一个线程（网络收发与执行命令），除此之外还有几个bio后台线程，包含了处理关闭文件和刷盘的后台线程以及lazyfee线程  
              redis中的三个后台删除命令  
                  dbAsyncDelete 
                  flushdb async 
                  flushall async
              这三个都会调用emptyDbAsnyc来清空数据库
              redis中的4个后台删除配置项
                slave-lazy-flush slave接收完RDB后清空数据选项
                lazyfree-lazy-eviction 
                lazyfree-lazy-expire 过期key放入lazyfree删除
                lazyfree-lazy-server-del 内部删除放入lazyfree 比如rename 修改oldkey名称变为newkey,若newkey已存在，会放入lazyfree中删除


