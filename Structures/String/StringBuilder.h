// Author: 绝迹的星 
// Created on 2023/12/12


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "String.c"
#ifndef C_STRINGBUILDER_H
#define C_STRINGBUILDER_H

#define DefaultSize 16
typedef signed char byte;
/** use serialVersionUID for interoperability */
long long serialVersionUID = 4383685877147921099L;
byte LATIN1 = 0;
typedef struct StringBuilder {
    /** The value is used for character storage.*/
    byte *value;
    /** The count is the number of characters used.*/
    int count;
    int capacity;
    byte *EMPTYVALUE;

} StringBuilder;

void InitStringBuilder(StringBuilder *sb, int capacity);

void InitStringBuilderDefault(StringBuilder *sb);

void InitStringBuilderByString(StringBuilder *sb, String str);
void append(StringBuilder *sb, String str);
void appendNull(StringBuilder*sb);
void ensureCapacityInternal(StringBuilder *sb,int minimumCapacity);
int newCapacity(StringBuilder *sb,int minCapacity);
#endif //C_STRINGBUILDER_H
