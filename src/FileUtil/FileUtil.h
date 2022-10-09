#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdio.h>
#include <string>

void WriteInt(FILE* fileptr, int number);
int ReadInt(FILE* fileptr);
void WriteShort(FILE* fileptr, short value);
short ReadShort(FILE* fileptr);

std::string ReadString(FILE* fileptr);

#endif