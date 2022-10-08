#include "FileUtil.h"

#include <stdio.h>

void WriteInt(FILE* fileptr, int number) {
    if(sizeof(int) == 4) {
        putc(((char)(number >> (8*3))) & 0xff, fileptr);
        putc(((char)(number >> (8*2))) & 0xff, fileptr);
        putc(((char)(number >> (8*1))) & 0xff, fileptr);
        putc(((char)(number >> (8*0))) & 0xff, fileptr);
    } else {
        printf("no lol\n");
    }
}

int ReadInt(FILE* fileptr) {
    char part4 = getc(fileptr);
    char part3 = getc(fileptr);
    char part2 = getc(fileptr);
    char part1 = getc(fileptr);

    return (int) (((part4) << (8*3)) | ((part3) << (8*2)) | ((part2) << (8*1)) | ((part1) << (8*0)));
}

void WriteShort(FILE* fileptr, short value) {
    if(sizeof(short) == 2) {
        putc(((char)(value >> (8*1))) & 0xff, fileptr);
        putc(((char)(value >> (8*0))) & 0xff, fileptr);
    } else {
        printf("no lol\n");
    }
}

short ReadShort(FILE* fileptr) {
    char part2 = getc(fileptr);
    char part1 = getc(fileptr);

    return (short) ((part2 << (8*1)) | (part1));
}