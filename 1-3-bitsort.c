/*
 * =====================================================================================
 *
 *       Filename:  1-3-bitsort.c
 *
 *    Description:  用1-2的位运算的方法，对1-4生成的电话号码进行排序
 *
 *        Version:  1.0
 *        Created:  2013年06月06日 16时56分53秒
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
#include "1-2-bit.h"

int bitsort(char * filename){
  FILE * fp = fopen(filename, "r");
  unsigned int allbits[1 + N/BITSPERWORD] = {0};

  unsigned int i;

  unsigned int tmp;
  while(fscanf(fp, "%d", &tmp) > 0){
    set(allbits, tmp);
  }
  fclose(fp);

  char * result = "result.txt";
  fp = fopen(result, "w");
  for(i = 1000000; i < N; i++){
    if(test(allbits, i) > 0){
      fprintf(fp, "%d\n", i);
    }
  }
  fclose(fp);

  return 0;
}

int main(int argc, char * argv []){
  bitsort(argv[1]);
  return 0;
}
