#ifndef SAVE_WINDOW_H
#define SAVE_WINDOW_H

#include "../GUI/Window.h"
#include <string>

class Editor;

class SaveWindow : public Window {
    public:
    SaveWindow(Editor* editor);

    Editor* m_editor;
    std::string m_savename;
};

#endif