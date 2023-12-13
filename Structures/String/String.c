// Author: 绝迹的星 
// Created on 2023/11/2
// - Hello World.
// - You are my world too.


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Status.h"

typedef struct {
    char *ch;
    int length;
} String;
bool IsEmpty(String str){
    return str.length==0;
}
/**
 * 给字符串赋值
 * @param str 要赋值的字符串
 * @param chars 源字符数组
 */
Status StrAssign(String *str, char *chars) {
    if (str->ch) free(str->ch);  //释放T原有空间
    int len1 = 0; //用于记录chars的长度len1
    char *c1 = chars;
    while (*c1++) {
        len1++;//求长度
    }
    if (len1 == 0) {   //判断要复制的子串是否为空
        str->ch = NULL; //为空则将T->ch指向NULL
    } else {  //不为空
        str->ch = malloc(sizeof(char) * (len1 + 1)); //多出一块空间存储'\0'
        if (!str->ch) exit(OVERFLOW);
        for (int i = 0; i <= len1; i++) {//i==len1为'\0'
            str->ch[i] = chars[i];//拷贝
        }
    }
    str->length = len1;
    return OK;
}

void InitString(String *S) {
    S->length = 0;
    S->ch = NULL; //防止S.ch指针在使用时发生未定义的行为
}

int StrLength(String S) {
    return S.length;
}

int StrCompare(String S, String T) {
    int minLen = S.length > T.length ? T.length : S.length;
    for (int i = 0; i < minLen; i++) {
        if (S.ch[i] != T.ch[i]) {
            return S.ch[i] - T.ch[i];
        }
    }
    return S.length - T.length;
}

Status ClearString(String *S) {
    free(S->ch);
    S->ch = NULL;
    S->length = 0;
    return OK;
}

Status ConCat(String *S, String S1, String S2) {
    if (S->ch) free(S->ch); //释放旧空间
    // 分配存储空间
    S->ch = malloc(sizeof(char) * (S1.length + S2.length + 1));
    if (!S->ch) exit(OVERFLOW);
    // 将S1和S2存入S中
    S->length = S1.length + S2.length;
    for (int i = 0; i < S1.length; i++) {
        S->ch[i] = S1.ch[i];
    }
    for (int i = 0; i <= S2.length; i++) {//i==S2.length为\0字符
        S->ch[i + S1.length] = S2.ch[i];
    }
    return OK;
}

/**
 * 用Sub返回字符串S的 索引pos起,长度为len的子串
 * @param Sub 接收对象
 * @param S 源字符串
 * @param start 起始索引
 * @param len 拷贝长度
 */
Status SubString(String *Sub, String S, int start, int len) {
    //校验参数合法性
    if (start < 0 || start >= S.length || len < 0 || len + start >= S.length) {
        return ERROR;
    }
    if (Sub->ch) free(Sub->ch);//释放旧空间
    Sub->ch = malloc(sizeof(char) * (len + 1));//开辟新空间
    if (!Sub->ch)exit(ERROR);
    for (int i = 0; i < len; i++) {//拷贝len个
        Sub->ch[i] = S.ch[i + start];
    }
    Sub->ch[len] = '\0';//最后一位置为\0
    Sub->length = len;
    return OK;
}
