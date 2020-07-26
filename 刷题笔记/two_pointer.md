## lc75 Sort Colors

Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

样例 
输入 [2,0,2,1,1,0]
输出 [0,0,1,1,2,2]

### 思路

1. map表统计每个数字的个数，然后为数组赋值
2. 双指针法，end0表示0结束的区， 
   * 0 - end0 partition 0   
   * end0+1 - end1  partition1
   * start2 - size -1 partition2
end0 = 0, end1 = 0, start2 = size-1
while end1 <= start2
  if a[end1] == 0
     swap(a[end0++], a[end1++])
  else if a[end1] == 1
     end1++
  else 
     swap(a[end1], a[start2--]);
