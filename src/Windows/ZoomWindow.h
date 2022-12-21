#ifndef ZOOM_WINDOW_H
#define ZOOM_WINDOW_H

#include "../GUI/Window.h"

class Editor;

class ZoomWindow : public Window {
    public:
    ZoomWindow(Editor* editor);

    Editor* m_editor;
};

#endif