/*
 * =====================================================================================
 *
 *       Filename:  bigrand.c
 *
 *    Description:  至少返回30个随机位
 *
 *        Version:  1.0
 *        Created:  2013年05月31日 17时41分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zbhknight
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>

int bigrand(){
  return RAND_MAX*rand() + rand();
}

int randint(int l, int u){
  return l + bigrand()%(u-l+1);
}

int main(){
  printf("%d\n%d\n", bigrand(), RAND_MAX);
}
