/*
 * =====================================================================================
 *
 *       Filename:  2-1.c
 *
 *    Description:  输入单词，在字典中中搜索所有这个单词通过改变字母顺序可产生的单词, \
 *    需要用到 glib 库
 *
 *        Version:  1.0
 *        Created:  2013年06月12日 01时38分53秒
 *       Revision:  none
 *       Compiler:  gcc `pkg-config --cflags --libs glib-2.0
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

char * sortWord(char * word){
  //把单词按照字母顺序排序
  int wordSize = strlen(word);
  int i, j;
  char * newWord = malloc( (wordSize + 1) * sizeof(char) );
  memcpy(newWord, word, wordSize + 1);
  char tmp;
  for(i = 0; i < wordSize; i++){
    for(j = i + 1; j < wordSize; j++){
      if(newWord[j] < newWord[i]){
        tmp = newWord[i];
        newWord[i] = newWord[j];
        newWord[j] = tmp;
      }
    }
  }
  return newWord;
}

char * genTag(char * word, char * buffer){
  //把字母已经排序好的单词生成特征字符串
  char * newWord = sortWord(word);
  char * appendPosition;
  char lastChar = '\0';
  int i, lastCount = 0;
  appendPosition = buffer;
  for(i = 0; i < strlen(newWord); i++){
    if(newWord[i] == lastChar){
      lastCount++;
    } else {
      if(lastChar != '\0'){
        sprintf(appendPosition, "%d%c", lastCount, lastChar);
        appendPosition = buffer + strlen(buffer);
      }
      lastCount = 1;
      lastChar = newWord[i];
    }
  }
  sprintf(appendPosition, "%d%c", lastCount, lastChar);
  return buffer;
}

int readCompare(char * wordTag, char *** result){
  //在没有预处理的情况，逐个读入单词，生成特征字符串，比较
  FILE * fp = fopen("EnglishWords.txt", "r");
  char buffer[50];
  char word[50], * appendPosition;
  int match = 0;
  char * matchedWords = malloc(1024 * sizeof(char));
  appendPosition = matchedWords;
  while(fscanf(fp, "%s", word) > 0){
    //printf("debug:%s\n", word);
    genTag(word, buffer);
    if(strcmp(wordTag, buffer) == 0){
      //printf("%s %s\n", word, wordTag);
      match++;
      sprintf(appendPosition, "%s", word);
      appendPosition += strlen(word) + 1;
    }
  }
  fclose(fp);

  *result = malloc(match * sizeof(char *));
  int i, next = 0;
  for(i = 0; i < match; i++){
    (*result)[i] = matchedWords + next;
    next += strlen((*result)[i]) + 1;
    //printf("debug:%s\n", (*result)[i]);
  }
  return match;
}

int dealOne(char * argv[]){
  //处理单个单词的函数
  char * word = argv[1];
  char buffer[50];
  char * wordTag = genTag(word, buffer);
  char ** result = NULL;
  printf("%s\n", wordTag);
  int match = readCompare(wordTag, &result);
  //printf("debug:%d\n", match);
  int i;
  for(i = 0; i < match; i++){
    printf("%s\n", result[i]);
  }
  return 0;
}


typedef struct {
  //存储符合要求的单词的结构体
  int numOfItems;
  char * words[20];
}dictItem;

static char init_word[50];

GTree * initDict(char * filename){
  //读入单词文件，初始化特征字符树
  GTree * wordTree = g_tree_new((GCompareFunc)strcmp);
  //printf("debug:in:%X\n", (unsigned int)wordTree);

  FILE * fp = fopen(filename, "r");
  char * wordTag;
  dictItem * tmpItem;
  gpointer keyAddress;
  while(fscanf(fp, "%s", init_word) > 0){
    wordTag = malloc(50 * sizeof(char));
    genTag(init_word, wordTag);
    keyAddress = g_tree_lookup(wordTree, wordTag);
    if(keyAddress != NULL){
      //printf("debug:%s:found:%X:%s\n", init_word, (unsigned int)keyAddress, wordTag);
      tmpItem = (dictItem *)keyAddress;
    } else {
      //printf("debug:%s:notfound:%X:%s\n", init_word, (unsigned int)keyAddress, wordTag);
      tmpItem = malloc(sizeof(dictItem));
      tmpItem->numOfItems = 0;
    }

    tmpItem->words[tmpItem->numOfItems] = malloc((strlen(init_word) + 1) * sizeof(char));
    strcpy(tmpItem->words[tmpItem->numOfItems], init_word);
    tmpItem->numOfItems++;

    if(! keyAddress){
      g_tree_insert(wordTree, wordTag, tmpItem);
      //printf("debug:insert:%s:%s:%X\n", wordTag, init_word, (unsigned int)tmpItem);
    }
  }

  fclose(fp);
  //printf("debug:nodes:%d\n", g_tree_nnodes(wordTree));
  return wordTree;
}

int dealMulti(){
  //预先生成特征字符数，从标准输入读入单词查询
  GTree * wordTree = initDict("EnglishWords.txt");
  //printf("debug:out:%X\n", (unsigned int)wordTree);
  char * wordTag, buffer[50], word[50];
  int i;
  while(scanf("%s", word)){
    wordTag = genTag(word, buffer);
    dictItem * tmp = (dictItem *)g_tree_lookup(wordTree, wordTag);
    if(tmp){
      printf("%d\n", tmp->numOfItems);
      for(i = 0; i < tmp->numOfItems; i++){
        printf("%s\n", tmp->words[i]);
      }
    }
  }
  return 0;
}

int main(int argc, char * argv []){
  if(argc == 2){
    dealOne(argv);
  } else {
    dealMulti();
  }
  return 0;
}
