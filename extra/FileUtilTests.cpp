// g++ ./extra/FileUtilTests.cpp ./src/FileUtil/FileUtil.cpp -o main

#include <stdio.h>

#include "src/FileUtil/FileUtil.h"

template<typename T>
void CheckResult(T expectedvalue, T input) {
    if(expectedvalue != input) {
        printf("FAILED : expected value : %i | input : %i\n", expectedvalue, input);
    } else {
        printf("SUCCESS\n");
    }
}



int main() {
    FILE* myfile = fopen("testfilelol", "w");

    WriteShort(myfile, -33);
    WriteShort(myfile, 65535);

    WriteInt(myfile, -424753310);
    WriteInt(myfile, -42);
    WriteInt(myfile, 128);
    WriteInt(myfile, 424753310);

    WriteInt(myfile, (unsigned int)3947483647);

    fclose(myfile);
    
    myfile = fopen("testfilelol", "r");

    CheckResult<short>(-33, ReadShort(myfile));
    CheckResult<short>(65535, ReadShort(myfile));

    CheckResult<int>(-424753310, ReadInt(myfile));
    CheckResult<int>(-42, ReadInt(myfile));
    CheckResult<int>(128, ReadInt(myfile));
    CheckResult<int>(424753310, ReadInt(myfile));

    CheckResult<unsigned int>(3947483647, ReadInt(myfile));

    fclose(myfile);


    //printf("int  : %x\n", (int)3947483647);
    //printf("uint : %x\n", (unsigned int)3947483647);
    //printf("long : %lx\n", (long)3947483647);

    return 0;
}