#include "MainWindow.h"

#include <raylib.h>

int g_maxfps;

int g_winwidth;
int g_winheight;

void InitMainWindow(int width, int height, const char* title) {
    InitWindow(width, height, title);
    g_winwidth = width;
    g_winheight = height;
}

void ResizeMainWindow(int newwidth, int newheight) {
    if(newwidth != g_winwidth || newheight != g_winheight) {
        SetWindowSize(newwidth, newheight);
    }

    g_winwidth = newwidth;
    g_winheight = newheight;
}

void SetMainFPS(int fps) {
    g_maxfps = fps;
    SetTargetFPS(fps);
}