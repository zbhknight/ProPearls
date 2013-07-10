/*
 * =====================================================================================
 *
 *       Filename:  8-1-find_maxsum_period.c
 *
 *    Description:  找出整数数组中，连续和最大的区间
 *
 *        Version:  1.0
 *        Created:  2013年06月21日 22时41分34秒
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
#include <time.h>

struct node {
  int max_period;
  int left;
  int right;
};

int max(int a, int b){
  return a>b?a:b;
}

int split_find(int nums[], int start, int end){
  if(start > end)
    return 0;
  if(start == end)
    return max(0, nums[start]);

  int middle = (start + end) / 2;
  int leftmax, rightmax, middlemax;
  leftmax = split_find(nums, start, middle);
  rightmax = split_find(nums, middle + 1, end);
  int middle_left = 0, middle_right = 0;
  int i, tmp_sum;
  tmp_sum = 0;
  for(i = middle; i >= start; i--){
    tmp_sum += nums[i];
    middle_left = max(middle_left, tmp_sum);
  }

  tmp_sum = 0;
  for(i = middle + 1; i <= end; i++){
    tmp_sum += nums[i];
    middle_right = max(middle_right, tmp_sum);
  }

  return max(max(leftmax, rightmax), middle_left + middle_right);
}

struct node * split_find_linear(int nums[], int start, int end){
  struct node * to_return = malloc(sizeof(struct node));

  if(start > end){
    to_return->max_period = 0;
    to_return->left = end;
    to_return->right = end;
    return to_return;
  }
  if(start == end){
    if(nums[start] >= 0){
      to_return->max_period = nums[start];
      to_return->left = start;
      to_return->right = start;
    } else {
      to_return->max_period = 0;
      to_return->left = start - 1;
      to_return->right = start - 1;
    }
    return to_return;
  }

  int middle = (start + end) / 2;
  struct node * leftnode, * rightnode;
  leftnode = split_find_linear(nums, start, middle);
  rightnode = split_find_linear(nums, middle + 1, end);
  int middle_left = 0, middle_right = 0;
  int i, tmp_sum;

  tmp_sum = 0;
  to_return->left = middle + 1;
  for(i = middle; i > leftnode->right; i--){
    tmp_sum += nums[i];
    if(tmp_sum > middle_left){
      middle_left = tmp_sum;
      to_return->left = i;
    }
  }
  if(tmp_sum + leftnode->max_period> middle_left){
    middle_left = tmp_sum + leftnode->max_period;
    to_return->left = leftnode->left;
  }

  tmp_sum = 0;
  to_return->right = middle;
  for(i = middle + 1; i < rightnode->left; i++){
    tmp_sum += nums[i];
    if(tmp_sum > middle_right){
      middle_right = tmp_sum;
      to_return->right = i;
    }
  }
  if(tmp_sum + rightnode->max_period> middle_right){
    middle_right = tmp_sum + rightnode->max_period;
    to_return->right = rightnode->right;
  }

  to_return->max_period = max(max(leftnode->max_period, rightnode->max_period), middle_left + middle_right);

  return to_return;
}

int scan_find(int nums[], int size){
  int max_lastperiod = 0,  max_endhere = 0;
  int i;
  for(i = 0; i < size; i++){
    max_endhere = max(0, max_endhere + nums[i]);
    max_lastperiod = max(max_lastperiod, max_endhere);
  }
  return max(max_lastperiod, max_endhere);
}

int main(int argc, char * argv[]){
  //int nums[10] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
  int size = atoi(argv[1]);
  int * nums = malloc(size * sizeof(int));
  int i;
  for(i = 0; i < size; i++){
    nums[i] = (random() % 1000) - 500;
  }
  clock_t t = clock();
  printf("%d\n", split_find(nums, 0, size - 1));
  t = clock() - t;
  printf("%f\n", ((float)t) / CLOCKS_PER_SEC);
  t = clock();
  printf("%d\n", scan_find(nums, size));
  t = clock() - t;
  printf("%f\n", ((float)t) / CLOCKS_PER_SEC);
  t = clock();
  struct node * p = split_find_linear(nums, 0, size - 1);
  printf("%d\n", p->max_period);
  t = clock() - t;
  printf("%f\n", ((float)t) / CLOCKS_PER_SEC);
  return 0;
}
