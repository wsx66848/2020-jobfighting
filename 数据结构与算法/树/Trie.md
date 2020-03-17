# Trie

## 性质

字典树/前缀树

* 根结点不包含字符，除根结点外每个结点都包含字符
* 从根结点到某一个结点(关键字标志位结点)，路径上的字符连接起来，为该结点对应的字符串
* 每个结点的所有子结点包含的字符都不相同

## 用途

1. 查找字符串
2. 统计词频
3. 字符串排序
   遍历一次所有关键字，将它们全部插入trie树，树的每个结点的所有儿子很显然地按照字母表排序，然后先序遍历输出Trie树中所有关键字（即一个完整地字符串)即可
4. 前缀匹配

## 与hash表比较

- 优点
  1. hash函数不合适时会产生大量哈希冲突影响查找效率，trie树不同关键字不会产生冲突
  2. trie树可以对关键字排序
  3. trie树不用求哈希值，对短字符串有更快的处理速度

- 缺点
  1. hash函数很好时，trie查找效率低于hash表
  2. 空间消耗大

## 效率

插入和查找效率均为O(m) m为字符串长度

## 实现

```cpp
#include <iostream>
#include <string>

#define MAX_CHILDREN 26

using namespace std;

typedef struct TrieNode {
    int count //词频
    TrieNode* children[MAX_CHILREN] // 0 - 25 表示 'a' - 'z'
}*Trie

trie createTrieNode() {
    trie node = new trie;
    for(int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    node->count = 0; 
    return node
}

void insert(trie root, string s) {
    int len = s.size();
    int i = 0;
    trie node = root
    while(i < len) {
        int index = s[i] - 'a';
        if(node->children[index] == NULL) {
            node->children[index] = createTrieNode();
        }
        node = node->children[index];
        i++;
    }
    node->count += 1;
}

//不存在返回0，存在则返回词频
int search(trie root, string s) {
    int len = s.size();
    int i = 0;
    trie node = root;
    while(i < len) {
        int index = s[i] - 'a';
        if(node->children[index] == NULL) return 0;
        node = node->children[index];
        i++;
    }

    if(node == NULL) return 0;
    else return node->count;
}
```
 
  