/*
 * =====================================================================================
 *
 *       Filename:  4-3-bsearchrecursive.c
 *
 *    Description:  递归二分查找
 *
 *        Version:  1.0
 *        Created:  2013年06月19日 17时40分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>

//int bsearchrecursive(int nums[], int start, int end, int to_search){
//  int middle;
//  if(end >= start && to_search >= nums[start] && to_search <= nums[end]){
//    middle = (start + end) / 2;
//    if(nums[middle] == to_search)
//      return middle;
//    if(nums[middle] > to_search){
//      return bsearchrecursive(nums, start, middle - 1, to_search);
//    }
//    if(nums[middle] < to_search){
//      return bsearchrecursive(nums, middle + 1, end, to_search);
//    }
//  }
//  return -1;
//}

int bsearchrecursive(int nums[], int start, int end, int to_search){
  int left_value, right_value = nums[end];
  int middle;
  if(start == -1)
    left_value = -1;
  else
    left_value = nums[start];
  if(end > start && to_search > left_value && to_search <= right_value){
    middle = (start + end) / 2;

    if(end == start + 1){
      if(left_value == to_search)
        return start;
      else if(right_value == to_search)
        return end;
      else
        return -1;
    }

    if(to_search <= nums[middle]){
      return bsearchrecursive(nums, start, middle, to_search);
    } else {
      return bsearchrecursive(nums, middle, end, to_search);
    }
  }

  return -1;
}

int main(int argc, char * argv[]){
  int to_search = atoi(argv[1]);

  int test[5050], i, j, index = 0;
  for(i = 1; i <= 100; i++){
    for(j = 0; j < i; j++){
      test[index] = i;
      index++;
    }
  }

  int result = bsearchrecursive(test, -1, 5049, to_search);
  printf("%d %d %d\n", result, test[result-1], test[result]);
  return 0;
}
