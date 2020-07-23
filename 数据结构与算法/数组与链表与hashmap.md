# 数组与链表

数组: 内存中连续存放 
链表: 内存中不必连续存放，通过指针连接起来

数组元素访问方便  链表插入、删除方便

hashmap: O(1)的搜索复杂度，但是无序，不支持范围查询

## 链表结构

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
  ```

## 反转链表

非递归  每遍历一个结点就翻转

```cpp
ListNode* reverse(ListNode* head) {
    if(head == NULL || head->next == NULL) return head;
    ListNode* pHead = NULL;
    while(head) {
        ListNode* tmp = head->next;
        head->next = pHead;
        pHead = head;
        head = tmp;
    }
    return pHead;
}
```

递归

```cpp
ListNode* reverse(ListNode* head) {
    if(head == NULL || head->next == NULL) return head;
    ListNode* last = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return last;
}
```

## 反转前K个结点

非递归
```cpp
ListNode* reverseFirstK(ListNode* head, int k) {
    if(head == NULL || head->next == NULL || k < 2) return head;
    ListNode* pHead = NULL;
    ListNode* node = head;
    while(node && k--) {
        ListNode* tmp = node->next;
        node->next = pHead;
        pHead = node;
        node = tmp;
    }
    head->next = node;
    return pHead;
}
```

递归 使用successor来记录翻转边界的后继节点

```cpp
ListNode* successor;
ListNode* reverseFirstK(ListNode* head, int k) {
   if(k == 1) {
       successor = head->next;
       return head;
   }
   ListNode* last = reverseFirstK(head->next, k - 1);
   head->next->next = head;
   head->next = successor;
   return last;
}
```

## 反转[m, n]的链表结点

递归
```cpp
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if(m == 1) return reverseFirstK(head, n);
    head->next = reverseBetween(head->next, m - 1, n - 1);
    return head;
}

非递归
```cpp
ListNode* reverseBetween(ListNode* head, int m, int n) {
   if(head == NULL || head->next == NULL) return head;
   ListNode root(0);
   root.next = head;
   ListNode* p = &root;
   ListNode* q = &root;
   m--;
   while(m--) p = p->next; //m-1 结点
   while(n--) q = q->next; // n结点

   ListNode* tail = q->next;
   q->next = NULL;
   ListNode* cur = p->next;
   while(cur) {
       ListNode* tmp = cur->next;
       cur->next = tail;
       tail = cur;
       cur = tmp;
   }
   p->next = tail;
   return root.next;
}
```

## K个一组反转链表

```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    if(head == NULL || head->next == NULL || k < 2) return head;
    ListNode* temp = head;
    for(int i = 0; i < k; i++) {
        if(temp == NULL) return head;
        temp = temp->next;
    }
    ListNode* last = reverseFirstK(head, k);
    head->next = reverseKGroup(head->next, k);
    return last;
}
```

## 螺旋数组

1. 输入矩阵，螺旋打印

常规题，只需设定每圈的边界值即可 (redge, rEdge) (cedge, cEdge)
``` cpp
vector<int> printMatrix(vector<vector <int>>& matrix) {
    if(matrix.size() == 0 || matrix[0].size() == 0) return {};
    vector<int> res;
    int cnt = matrix.size() * matrix[0].size();
    int x = 0, y = 0, 
    redge = 0, rEdge = matrix.size() - 1
    cedge = 0, rEdge = matrix[0].size() - 1;
    for(; cnt > 0; --cnt) {
        res.push_back(matrix[x][y]);
        if(x == redge) {
            if(y < cEdge) y++;
            else x++;
            continue;
        }
        if(y == cEdge) {
            if(x < rEdge) x++;
            else y--;
            continue;
        }
        if(x == rEdge) {
            if(y > cedge) y--;
            else x--;
            continue;
        }
        if(y == cedge) {
            if(x > redge + 1) x--;
            else {
                ++redge;
                ++cdge;
                --rEdge;
                --cEdge;
                y++;
            }
        }
    }
    return res;
}
```

1. 给定数字n，输出n*n矩阵的螺旋序列，要求空间复杂度O(1)
例: n = 4  
1  2  3  4
12 13 14 5
11 16 15 6
10 9  8  7

空间复杂度O(1) 无法创建一个矩阵将数字先填进去，需要寻找规律
数字n 

圈数round = (n + 1) / 2

点(i,j) i,j从1开始算  所处的圈level = min(i - 1, j - 1, n - i, n - j) level 从 0 到 round - 1

level的一圈数字个数为 4 * (n - (1 + 2 *level))

对于level圈，改圈起始数字是 init = 4 * level * (n - level) + 1

对于level = i - 1时，位于这一圈开始的行 即从左到右的行 (i,j)的值为 init + j - 1 - level
对于level = n - j时，位于这一圈从上向下的列 (i,j) = init + n - 2 * level - 1 + i - 1 - level
对于level = n - i时，位于这一圈从右往左的行 (i,j) = init + 2 * n - 4 * level - 2 + n - level - j
对于level = j - 1时，位于这一圈从下往上的列 (i,j) = init + 3 * n - 6 * level - 3 + n - level - i
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define min(a, b) ((a) < (b)? (a) : (b))
void printMatrix(int n)
{
	// 预先存下已用的数字数 (由于要求O(1)大小空间，因此这个数组后续未曾使用)
	int *amount = new int[n / 2 + 1];
	amount[0] = 0;
	for (int i = 1; i <= n / 2; ++i)
		amount[i] = amount[i - 1] + 4 * (n - 2 * i + 1);

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
		 	// 获得当前的点所在的圈数
			int level = min(min(i - 1, j - 1), min(n - i, n - j));
			// 该圈起始数字
			// int initial = amount[level] + 1;
			int initial = 4 * level * n + 1;
			if (i - 1 == level) cout << setw(5) << initial + j - 1 - level;
			else if (n - j == level) cout << setw(5) << initial + n - 2 * level - 1 + i - 1 - level;
			else if (n - i == level) cout << setw(5) << initial + 2 * n - 4 * level - 2 + n - level - j;
			else cout << setw(5) << initial + 3 * n - 6 * level - 3 + n - level - i;
		}
		cout << endl;
	}
}

int main()
{
	for (int n; cin >> n;)
		printMatrix(n);
	return 0;
}
```

## 哈希表

1. 哈希表桶的个数为什么最好是2<sup>n</sup>？  
     * 对一个数据分到哪个桶里，计算方式为hash(key) % number(buckets) 取余操作比较耗时，如果桶个数是2<sup>n</sup>, 那么可以用位操作来代替取余计算。具体做法是2<sup>n</sup> -  1 的二进制表示最后的位数都是1（比如8，减一之后二进制是0111，或者16，二进制是01111），这样用hash(key) & (number(buckets) - 1)，结果就是hash(key) 的最后几位，这个结果是小于number(buckets)的，而位运算又比较快，所以用位运算更合适
     * 在扩容时，如果本来哈希桶的个数是2的n此方，扩容的时候扩成2倍，成为2的n+1次方，根据上面的计算方法，此时多出来的一位如果是0的话，那么key所在的哈希桶是不变的，所以减少数据的迁移量
2. 为什么java里面的hashmap等到8时链表会变成红黑树？
   链表比红黑树的好处是占用空间较小，因为链表一个指针，红黑树两个指针还要记录颜色值。根据泊松分布，平均分布的hash表的桶里的链表长度达到8的概率是百万分之一，并且在长度为8的时候，单链表的平均复杂度是4，红黑树平均复杂度是3，所以转换结构