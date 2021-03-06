//
// Created by wyb on 15-11-19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "register.h"

char* StringUpper (const char* src)
{
    int len = strlen(src);
    char* dest;
    dest=(char*)malloc(sizeof(char)*len);
    int i;
    for (i = 0; i <= len; ++i)
        if(src[i]>='a'&&src[i]<='z')
            dest[i]=src[i]-32;
        else
            dest[i]=src[i];
    return dest;
}

unsigned int RegName2ID (const char* name)
{
    unsigned int i;
    for (i = 0; i < REG_SIZE; ++i)
        if(strcmp(name,kRegisterSet[i])==0)
            return i;
    return REG_SIZE+1;
}

int String2Int (const char* src)
{
    int dest=0, temp=0, sign=1;
    int len = (int)strlen(src), i=0;
    if (src[0]=='-') {
        sign=-1;
        i=1;
    }
    for( ; i<len; ++i)
        if (src[i]>='0'&&src[i]<='9') {
            temp = src[i]-'0';
            dest = dest*10 + temp;
        }
        else
            printf("string to int error\n");
    return sign*dest;
}
void swap (unsigned int* num1, unsigned int* num2)
{
    unsigned int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}