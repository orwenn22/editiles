#ifndef TEXTURE_LIST_WINDOW_H
#define TEXTURE_LIST_WINDOW_H

#include "../../GUI/Window.h"

class Editor;
class WindowManager;

class TextureListWindow : public Window {
    public:
    TextureListWindow(Editor* editor);

    Editor* m_editor;
};

#endif