#include <raylib.h>

#include "Editor.h"
#include "GUI/MainWindow.h"
#include "GUI/Mouse/MouseObject.h"
#include "Level.h"
#include "ParseFunctions.h"

#include <regex>

Editor* g_editor;

void OpenEditor(int argc, const char* argv[]) {
    InitMainWindow(960, 540, "editiles");
    SetMainFPS(120000);

    Editor* editor = new Editor();
    g_editor = editor;

    if(argc == 2) {
        editor->LoadFromFile(argv[1]);
    }

    while (!WindowShouldClose()) {
        editor->Update();
        
        BeginDrawing();
            ClearBackground(BLACK);
            editor->Draw();
            //DrawPixel(g_winwidth/2, g_winheight/2, RED);
            DrawFPS(10, 10);
        EndDrawing();
    }

    printf("QUITTING !!1!1!\n");
    delete editor;
    CloseWindow();
};

int ResizeCommand(int argc, const char* argv[]) {
    std::string inputfilename = argv[2];

    int newwidth = std::stoi(argv[3]);
    int newheight = std::stoi(argv[4]);
                
    std::string outputfilename;
    if(argc == 6) outputfilename = argv[5];
    else {
        outputfilename = inputfilename;
        int lastslash = outputfilename.find_last_of("/");
        outputfilename = outputfilename.substr(0, lastslash+1) 
                        + "new_" 
                        + outputfilename.substr(lastslash+1, outputfilename.size());
    }

    printf("%s\n", outputfilename.c_str());

    Level* inputlvl = ParseLVLFile(inputfilename);
    if(inputlvl == NULL) return 1;

    inputlvl->Resize(newwidth, newheight);

    inputlvl->Save(outputfilename);
    delete inputlvl;

    return 0;
}



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
        else {      //help
            printf("Editiles CLI help\n=================\n\n");

            printf("Open editiles GUI\n");
            printf("    %s\n\n", argv[0]);

            printf("Open and edit a file with the GUI\n");
            printf("    %s <input file .lvl>\n\n", argv[0]);

            printf("Resize a lvl file\n");
            printf("    %s -resize <input file> <new width> <new height> (<output name>)\n\n", argv[0]);
        }
    }
    
    return 0;
}