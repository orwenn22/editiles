#ifndef NEW_LEVEL_WINDOW_H
#define NEW_LEVEL_WINDOW_H

#include "../GUI/Window.h"

class Editor;
class WindowManager;

//TODO make this window create a new editor instead of a window.
//     this will require to make the window a part of the Application and not the Editor.
class NewLevelWindow : public Window {
    public:
    NewLevelWindow(Editor* editor);

    int m_vargridwidth;
    int m_vargridheight;

    int m_varboxwidth;
    int m_varboxheight;

    Editor* m_editor;
};

#endif