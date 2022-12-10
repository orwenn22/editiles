#include <raylib.h>

#include <stdio.h>
#include <string>

#include "CLI.h"


int main(int argc, const char* argv[]) {
    if(argc == 1) {
        OpenEditor(argc, argv);
    }
    else if(argc == 2 && argv[1][0] != '-') {
            OpenEditor(argc, argv);
    }
    else {  //argv > 2
        if(std::string(argv[1]) == "-resize") {
            if(argc == 5 || argc == 6) {
                ResizeCommand(argc, argv);
            } else {
                printf("%s -resize <input file> <new width> <new height> (<output name>)\n", argv[0]);
            }
        }
        else if(std::string(argv[1]) == "-expand") {
            if(argc == 7 || argc == 8) {
                ExpandCommand(argc, argv);
            } else {
                printf("%s -expand <input file> <top> <left> <right> <bottom> (<output name>)\n", argv[0]);
            }
        }
        else {      //help
            HelpCommand(argc, argv);
        }
    }
    
    return 0;
}