/*
 * =====================================================================================
 *
 *       Filename:  1-2-bit.h
 *
 *    Description:  头文件
 *
 *        Version:  1.0
 *        Created:  2013年06月06日 17时42分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

void set(unsigned int [], unsigned int);
void clr(unsigned int [], unsigned int);
unsigned int test(unsigned int [], unsigned int);

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000

