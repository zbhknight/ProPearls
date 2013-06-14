/*
 * =====================================================================================
 *
 *       Filename:  2-2-getreplica.c
 *
 *    Description:  把字符串 ab 变成 ba
 *
 *        Version:  1.0
 *        Created:  2013年06月13日 01时01分49秒
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
#include <string.h>

void part_move_recursive(char ** ab, int start, int breakpoint, int end){
  int start_length = breakpoint - start + 1;
  int end_length = end - breakpoint;
  if(start_length == 0 || end_length == 0)
    return;

  int to_exchange;
  char * tmp_buffer;
  if(end_length == start_length){
    tmp_buffer = malloc(start_length * sizeof(char));
    memcpy(tmp_buffer, *ab + start, start_length);
    memcpy(*ab + start, *ab + breakpoint + 1, end_length);
    memcpy(*ab + breakpoint + 1, tmp_buffer, end_length);
    free(tmp_buffer);
    return;
  } else if(end_length > start_length) {
    to_exchange = end - start_length + 1;
    tmp_buffer = malloc(start_length * sizeof(char));
    memcpy(tmp_buffer, *ab + start, start_length);
    memcpy(*ab + start, *ab + to_exchange, start_length);
    memcpy(*ab + to_exchange, tmp_buffer, start_length);
    //printf("%s\n", *ab);
    free(tmp_buffer);

    part_move_recursive(ab, start, breakpoint, to_exchange - 1);
  } else if(start_length > end_length){
    to_exchange = breakpoint - end_length + 1;
    tmp_buffer = malloc(end_length * sizeof(char));
    memcpy(tmp_buffer, *ab + breakpoint + 1, end_length);
    memcpy(*ab + breakpoint + 1, *ab + to_exchange, end_length);
    memcpy(*ab + to_exchange, tmp_buffer, end_length);
    //printf("%s\n", *ab);
    free(tmp_buffer);

    part_move_recursive(ab, start, to_exchange - 1, breakpoint);
  }
}

void part_move(char ** ab, int breakpoint){
  part_move_recursive(ab, 0, breakpoint, strlen(*ab) - 1);
}

void get_reverse(char ** ab, int start, int end){
  int i, j;
  char tmp;
  for(i = start; i <= (start + end)/2; i++){
    j = start + end - i;
    if( i != j){
      tmp = (*ab)[i];
      (*ab)[i] = (*ab)[j];
      (*ab)[j] = tmp;
    }
  }
}

void double_reverse(char ** ab, int breakpoint){
  get_reverse(ab, 0, breakpoint);
  get_reverse(ab, breakpoint + 1, strlen(*ab) - 1);
  get_reverse(ab, 0, strlen(*ab) - 1);
}

int gcd(int a, int b){
  while(a != b){
    if(a > b)
      a -= b;
    else
      b -= a;
  }
  return a;
}

void magic_jump(char ** ab, int breakpoint){
  int rotdist = breakpoint + 1;
  int string_length = strlen(*ab);
  int gcdnum = gcd(rotdist, string_length);
  int i, j, k;
  char tmp;
  for(i = 0; i < gcdnum; i++){
    j = i;
    tmp = (*ab)[i];
    while(1){
      k = j + rotdist;
      if(k >= string_length)
        k -= string_length;
      if(k == i)
        break;
      (*ab)[j] = (*ab)[k];
      j = k;
    }
    (*ab)[j] = tmp;
  }
}

int main(int argc, char * argv[]){
  int breakpoint = atoi(argv[1]);
  char * ab = malloc(11 * sizeof(char));
  strcpy(ab, "1234567890");
  printf("%s\n", ab);
  part_move(&ab, breakpoint);
  printf("%s\n", ab);
  double_reverse(&ab, strlen(ab) - 2 - breakpoint);
  printf("%s\n", ab);
  magic_jump(&ab, breakpoint);
  printf("%s\n", ab);
  return 0;
}
