#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

extern int g_maxfps;

extern int g_winwidth;
extern int g_winheight;

void InitMainWindow(int width, int height, const char* title);
void ResizeMainWindow(int newwidth, int newheight);
void SetMainFPS(int fps);

#endif