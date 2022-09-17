#ifndef NEW_LEVEL_WINDOW_H
#define NEW_LEVEL_WINDOW_H

#include "../GUI/Window.h"

class WindowManager;

class NewLevelWindow : public Window {
    public:
    NewLevelWindow(WindowManager* winmanager);

    int m_vargridwidth;
    int m_vargridheight;

    int m_varboxwidth;
    int m_varboxheight;
};

#endif