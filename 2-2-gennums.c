/*
 * =====================================================================================
 *
 *       Filename:  2-2-gennums.c
 *
 *    Description:  为2-2生成测试文件
 *
 *        Version:  1.0
 *        Created:  2013年06月12日 22时05分49秒
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

#define TOTAL 15000000
#define MAXINT 14748364
#define MORENUM 51635

int main(){
  FILE * fp = fopen("allint.txt", "w");
  unsigned int i;
  for(i = 0; i <= MAXINT; i++){
    fprintf(fp, "%u\n", i);
    if(rand() < MORENUM){
      fprintf(fp, "%u\n", i);
    }
  }
  fclose(fp);
  return 0;
}
