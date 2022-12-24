#ifndef NEW_LEVEL_WINDOW_H
#define NEW_LEVEL_WINDOW_H

#include "../GUI/Window.h"

class Application;
class WindowManager;

class NewLevelWindow : public Window {
    public:
    NewLevelWindow(Application* app);

    int m_vargridwidth;
    int m_vargridheight;

    int m_varboxwidth;
    int m_varboxheight;

    Application* m_app;
};

#endif