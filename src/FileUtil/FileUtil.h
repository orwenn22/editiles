#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdio.h>

void WriteInt(FILE* fileptr, int number);
int ReadInt(FILE* fileptr);
void WriteShort(FILE* fileptr, short value);
short ReadShort(FILE* fileptr);

#endif