## Laravel

## 服务容器定义
Laravel服务容器是一个用于管理类依赖和执行依赖注入的强大工具  
是工厂模式的升级版，服务容器为对象创建外部资源的同时，与外部资源没有任何关系，主要负责系统服务(缓存、认证、Session、持久化)的注册与解析，以及接口的绑定与解析

## IOC(控制反转) 与 DI(依赖注入)
IOC是指类的依赖不是在类内部生产（初始化、构造器中工厂方法、手动new），而是由外部生成，并以参数或者其他形式注入  
IOC容器就是指的类的依赖是由容器来解析并生成的，然后注入进去
DI是从类的角度说的，也是指自身的依赖是由外部注入的  
好处就是将类与依赖的具体实现解耦，达到高内聚(一个模块只专注做好一件事) 低耦合（不同模块之间的关联关系减少）的效果，使业务逻辑更加清晰，代码也容易扩展和维护  
**如何解耦？ 用接口**，接口就相当于是一个中间层，将类与它依赖的具体实现隔离开来

## 绑定方式

1. bind绑定
    * 绑定自身 
    ``` php
     $this->app->bind('App\Services\RedisEventPusher', null);
     ```
    * 绑定闭包
    * 绑定接口
2. bindif绑定
3. singleton绑定 只需要解析一次的类或接口到容器，接下来对容器的调用返回同一个实例
4. instance绑定 绑定一个已存在的实例到容器
5. context绑定  主要用于不同的类依赖同一个接口，但需要有不同的实现
``` php
$this->app->when(StorageController::class)
          ->needs(Filesystem::class)
          ->give(function () {
            Storage::class
          });//提供类名

$this->app->when(PhotoController::class)
          ->needs(Filesystem::class)
          ->give(function () {
             return new Storage();
          });//提供实现方式

$this->app->when(VideoController::class)
          ->needs(Filesystem::class)
          ->give(function () {
            return new Storage($app->make(Disk::class));
          });//需要依赖注入
```
6. 原始值绑定
``` php
$this->app->when('App\Http\Controllers\UserController')
          ->needs('$variableName')
          ->give($value);
```
7. 标签绑定

## 别名 与 解析
1. 可以递归设置别名
2. make解析
3. 自动注入（在方法中type hint依赖类型，由容器通过反射解析依赖）
4. 数组解析
5. 辅助函数 app解析
