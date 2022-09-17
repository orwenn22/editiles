#include <raylib.h>

#include "Editor.h"
#include "Mouse/MouseObject.h"

int g_maxfps = 120;

int g_winwidth = 960;
int g_winheight = 540;

Editor* g_editor;
MouseObject* g_mouse;

int main() {
    InitWindow(g_winwidth, g_winheight, "levedit");
    SetTargetFPS(g_maxfps);

    Editor* editor = new Editor();
    g_editor = editor;
    g_mouse = editor->m_mouse;

    while (!WindowShouldClose()) {
        editor->Update();
        
        BeginDrawing();
            ClearBackground(BLACK);
            editor->Draw();
            //DrawPixel(g_winwidth/2, g_winheight/2, RED);
            //DrawFPS(10, 10);
        EndDrawing();
    }

    delete editor;
    CloseWindow();
    return 0;
}