/*
 * =====================================================================================
 *
 *       Filename:  3-4-wordsuffix.c
 *
 *    Description:  配置单词连字符后缀
 *
 *        Version:  1.0
 *        Created:  2013年06月15日 00时54分00秒
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

int SUFFIX_NUM;
char * SUFFIX_CHAR;

void init_suffix(){
  char * raw = "et-ic al-is-tic s-tic p-tlic -lyt-lic ot-ic an-tic n-tic c-tic at-ic h-nic n-ic m-ic l-lic b-lic -clic l-ic h-ic f-ic d-ic -bic a-ic -mac i-ac";
  int raw_length = strlen(raw);

  SUFFIX_CHAR = malloc((raw_length + 1) * sizeof(char));
  memcpy(SUFFIX_CHAR, raw, raw_length + 1);

  char * change = SUFFIX_CHAR;
  int i;
  SUFFIX_NUM = 0;
  for(i = 0; i < raw_length; i++){
    if(*change == ' '){
      *change = '\0';
      SUFFIX_NUM++;
    }
    change++;
  }
  SUFFIX_NUM++;
  return;
}

char * search_suffix(char * word){
  char tmp_suffix[10];
  char * break_position, * buffer_position, * word_position,  * next_word = SUFFIX_CHAR;
  int i;
  char * to_return;
  for(i = 0; i < SUFFIX_NUM; i++){
    buffer_position = tmp_suffix;
    word_position = next_word;
    break_position = strchr(word_position, '-');
    while(break_position != NULL){
      strncpy(buffer_position, word_position, break_position - word_position);
      buffer_position += break_position - word_position;
      word_position = break_position + 1;
      break_position = strchr(word_position, '-');
    }
    strcpy(buffer_position, word_position);

    //printf("%s\n", tmp_suffix);
    if(strlen(word) >= strlen(tmp_suffix)){
      //printf("%s %s\n", word + strlen(word) - strlen(tmp_suffix), tmp_suffix);
      if(strcmp(word + strlen(word) - strlen(tmp_suffix), tmp_suffix) == 0){
        to_return = malloc( (strlen(next_word) + 1) * sizeof(char));
        strcpy(to_return, next_word);
        return to_return;
      }
    }

    next_word += strlen(next_word) + 1;
  }

  return NULL;
}

int main(int argc, char * argv[]){
  char * result;
  init_suffix();
  result = search_suffix(argv[1]);
  if(result != NULL){
    printf("%s\n", result);
  }
  return 0;
}
