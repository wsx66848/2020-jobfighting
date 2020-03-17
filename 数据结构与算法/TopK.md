TopK

1. 求前K大 前K小

前K大用小顶堆

```cpp
vector<int> topKMax(vector<int> num, int k) {
    int size = num.size();
    priority_queue<int, vector<int>, greater<int>> q;
    vector<int> res;
    for(int i = 0; i < size; i++) {
        if(i < K) {
            q.push(num[i]);
        } else {
            int Min = q.top(); //取最小
            if(num[i] > Min) {
                q.pop();
                q.push(num[i]);
            }
        }
    }
    while(! q.empty()) {
        res.push(q.top());
        q.pop();
    }
    return res;
}
```
前K小用大顶堆
```cpp
vector<int> topKMax(vector<int> num, int k) {
    int size = num.size();
    priority_queue<int> q;
    vector<int> res;
    for(int i = 0; i < size; i++) {
        if(i < K) {
            q.push(num[i]);
        } else {
            int Max = q.top(); //取最大
            if(num[i] < Max) {
                q.pop();
                q.push(num[i]);
            }
        }
    }
    while(! q.empty()) {
        res.push(q.top());
        q.pop();
    }
    return res;
}
```
O(nlogn)

2. 求第K大、第K小

两种思路 
一种类似上面的思路，前K小的大顶堆根节点就是第K小  前K大的小顶堆根节点就是第K大

另一种是用快速选择，类似快排的思路，当基准值的位置到达K时，若数组从小到大，则为第K小， 若数组从大到小，则为第K大
第K小
``` c++
int  quickSelect(int* a, int start, int end) {
      int left = start, right = end;
      int key = a[left];
      while(left < right) {
          while(left < right && a[right] >= key) right--;
          a[left] = a[right];
          while(left < right && a[left] < key) left++;
          a[right] = a[left];
      }
      a[left] = key;
      if(left < K -1) return quickSelect(a, left + 1, end);
      if(left > K - 1) return quickSelect(a, start, left - 1)
  }
  quickSelect(a, 0,  size - 1);
```