/*
 * =====================================================================================
 *
 *       Filename:  genrandom.c
 *
 *    Description:  随机生成随机数
 *
 *        Version:  1.0
 *        Created:  2013年06月01日 03时06分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zbhknight
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10000000

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(int argc, char * argv[]){
  int * allnum;
  allnum = malloc((MAX_NUM - 999999) * sizeof(int));
  int i;
  for(i = 1000000; i < MAX_NUM; i++){
    allnum[i - 1000000] = i;
  }

  int m = atoi(argv[1]);

  for(i = 0; i < m; i++){
    swap(&allnum[i], &allnum[rand()%(MAX_NUM - 999999)]);
  }

  FILE * fp = fopen("telnumbers.txt", "w");
  for(i = 0; i < m; i++){
    //printf("%d\n", allnum[i]);
    fprintf(fp, "%d\n", allnum[i]);
  }
  fclose(fp);

  return 0;
}
