#include "Application.h"
#include "Editor.h"
#include "FileUtil/PathUtil.h"
#include "GUI/MainWindow.h"
#include "GUI/Mouse/MouseObject.h"
#include "Level.h"
#include "ParseFunctions.h"


void OpenEditor(int argc, const char* argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(960, 540, "editiles");
    SetTargetFPS(120000);

    Application* app = new Application();

    if(argc == 2) {
        app->LoadFile(argv[1]);
    }

    while (!WindowShouldClose()) {
        app->Update();
        
        BeginDrawing();
            app->Draw();
            //DrawPixel(g_winwidth/2, g_winheight/2, RED);
            DrawFPS(10, 30);
        EndDrawing();
    }

    printf("QUITTING !!1!1!\n");
    delete app;
    CloseWindow();
};

int ResizeCommand(int argc, const char* argv[]) {
    std::string inputfilename = argv[2];

    int newwidth = std::stoi(argv[3]);
    int newheight = std::stoi(argv[4]);
                
    std::string outputfilename;
    if(argc == 6) outputfilename = argv[5];
    else {
        outputfilename = GetPathFromPath(inputfilename)
                        + "new_"
                        + GetNameFromPath(inputfilename);
    }

    printf("%s\n", outputfilename.c_str());

    Level* inputlvl = ParseLVLFile(inputfilename);
    if(inputlvl == NULL) return 1;

    inputlvl->Resize(newwidth, newheight);

    inputlvl->Save(outputfilename);
    delete inputlvl;

    return 0;
}

int ExpandCommand(int argc, const char* argv[]) {
    std::string inputfilename = argv[2];

    int top = std::stoi(argv[3]);
    int left = std::stoi(argv[4]);
    int right = std::stoi(argv[5]);
    int bottom = std::stoi(argv[6]);
                
    std::string outputfilename;
    if(argc == 8) outputfilename = argv[7];
    else {
        outputfilename = GetPathFromPath(inputfilename)
                        + "new_"
                        + GetNameFromPath(inputfilename);
    }

    Level* inputlvl = ParseLVLFile(inputfilename);
    if(inputlvl == NULL) return 1;

    inputlvl->Expand(top, left, right, bottom);

    inputlvl->Save(outputfilename);
    delete inputlvl;

    return 0;
}

int HelpCommand(int argc, const char* argv[]) {
    printf("Editiles CLI help\n=================\n\n");

    printf("Open editiles GUI\n");
    printf("    %s\n\n", argv[0]);

    printf("Open and edit a file with the GUI\n");
    printf("    %s <input file .lvl>\n\n", argv[0]);

    printf("Resize a lvl file\n");
    printf("    %s -resize <input file> <new width> <new height> (<output name>)\n\n", argv[0]);

    printf("Expand a lvl file\n");
    printf("    %s -expand <input file> <top> <left> <right> <bottom> (<output name>)\n", argv[0]);

    return 0; 
}