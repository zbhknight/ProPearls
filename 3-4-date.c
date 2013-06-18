/*
 * =====================================================================================
 *
 *       Filename:  3-4-date.c
 *
 *    Description:  日期转换程序
 *
 *        Version:  1.0
 *        Created:  2013年06月14日 16时48分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
//  localtime 这些函数每次返回的地址都是一样的，多次调用要小心

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define DAYSECS 86400

struct tm * time_fromstring(char * time_string){
  int year, month, day;
  sscanf(time_string, "%d-%d-%d", &year, &month, &day);
  struct tm * result = malloc(sizeof(struct tm));
  memset(result, 0, sizeof(struct tm));
  result->tm_year = year - 1900;
  result->tm_mon = month - 1;
  result->tm_mday = day;
  time_t tmp_time_t = mktime(result);
  memcpy(result, localtime(&tmp_time_t), sizeof(struct tm));
  //printf("debug:%s", asctime(result));
  //printf("debug:in:resultvalue:%x\n", (unsigned int)result);
  return result;
}

int diff_date(struct tm * start, struct tm * end){
  int diff_sec = difftime(mktime(end), mktime(start));
  return diff_sec % DAYSECS == 0?diff_sec/DAYSECS:diff_sec/DAYSECS + 1;
}

int get_wday(struct tm * day){
  return day->tm_wday;
}

int get_calendar(struct tm * day){
  int sizeoftm = sizeof(struct tm);
  struct tm head, tail;
  memset(&head, 0, sizeoftm);
  memset(&tail, 0, sizeoftm);
  head.tm_year = day->tm_year;
  head.tm_mon = day->tm_mon;
  head.tm_mday = 1;

  if(head.tm_mon + 1 >= 12){
    tail.tm_year = head.tm_year + 1;
    tail.tm_mon = 0;
  } else {
    tail.tm_year = head.tm_year;
    tail.tm_mon = head.tm_mon + 1;
  }
  tail.tm_mday = 1;
  time_t tmp;
  tmp = mktime(&head);
  memcpy(&head, localtime(&tmp), sizeoftm);

  tmp = mktime(&tail) - DAYSECS;
  memcpy(&tail, localtime(&tmp), sizeoftm);

  int before_blank = head.tm_wday;
  int first_weekday = head.tm_wday;
  char * next, * buffer = malloc(150 * sizeof(char));
  next = buffer;
  int i, count;
  for(i = 0; i < before_blank; i++){
    count = sprintf(next, "   ");
    next += count;
  }
  for(i = 1; i <= tail.tm_mday; i++){
    count = sprintf(next, "% 3d", i);
    next += count;
    if((first_weekday + i - 1) % 7 == 6){
      sprintf(next++, "\n");
    }
  }
  printf("%s\n", buffer);
  return 0;
}

int main(int argc,  char * argv[]){
  char * start_string = argv[1];
  char * end_string = argv[2];
  struct tm * start_date = time_fromstring(start_string);
  struct tm * end_date = time_fromstring(end_string);

  printf("start:%s", asctime(start_date));
  printf("end:%s", asctime(end_date));
  printf("date-period:%d\n", diff_date(start_date, end_date));
  printf("weekday:%d\n", get_wday(start_date));

  get_calendar(start_date);
  return 0;
}
