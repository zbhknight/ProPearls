/*
 * =====================================================================================
 *
 *       Filename:  1-2-bit.c
 *
 *    Description:  用位运算实现向量
 *
 *        Version:  1.0
 *        Created:  2013年06月06日 16时16分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

//#include <stdlib.h>
//#include <stdio.h>
#include "1-2-bit.h"

void set(unsigned int allbits [], unsigned int i){
  allbits[i >> SHIFT] |= (1 << (i & MASK));
}

void clr(unsigned int allbits [], unsigned int i){
  allbits[i >> SHIFT] &= ~(1 << (i & MASK));
}

unsigned int test(unsigned int allbits [], unsigned int i){
  return (unsigned int)(allbits[i >> SHIFT] & (1 << (i & MASK)));
}

//int main(){
//  int a[1 + N/BITSPERWORD] = {0};
//  set(a, 100);
//  printf("%d\n", test(a, 100));
//  return 0;
//}
