/*
 * =====================================================================================
 *
 *       Filename:  4-2-bsearchfirst.c
 *
 *    Description:  二分查找发。如果有多个重复元素，返回第一个
 *
 *        Version:  1.0
 *        Created:  2013年06月18日 17时06分29秒
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

//int bsearch_first(int nums[], int size, int to_search){
//  int middle, start = 0, end = size - 1;
//  while(nums[end] >= nums[start]){
//    middle = (start + end) / 2;
//    if(nums[middle] == to_search){
//      while(middle - 1 >= start && nums[middle - 1] == to_search){
//        middle--;
//      }
//      return middle;
//    }
//
//    if(nums[middle] > to_search){
//      end = middle - 1;
//    }
//    if(nums[middle] < to_search){
//      start = middle + 1;
//    }
//  }
//  return -1;
//}

int bsearch_first(int nums[], int size, int to_search){
  int middle, start = -1, end = size - 1;
  int left_value = -1, right_value = nums[end];
  while(end > start + 1 && to_search <= right_value && to_search > left_value){
    middle = (start + end) / 2;
    if(nums[middle] >= to_search){
      end = middle;
      right_value = nums[end];
    }
    if(nums[middle] < to_search){
      start = middle;
      left_value = nums[start];
    }
  }
  if(nums[start] == to_search)
    return start;
  else if(nums[end] == to_search)
    return end;
  else
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

  int result = bsearch_first(test, 5050, to_search);
  printf("%d %d %d\n", result, test[result-1], test[result]);
  return 0;
}
