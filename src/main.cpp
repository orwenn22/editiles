#include <raylib.h>

#include "Editor.h"
#include "GUI/MainWindow.h"
#include "GUI/Mouse/MouseObject.h"

Editor* g_editor;

int main(int argc, const char* argv[]) {
    InitMainWindow(960, 540, "levedit");
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
    return 0;
}