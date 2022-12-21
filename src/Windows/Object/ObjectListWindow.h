#ifndef OBJECT_LIST_WINDOW_H
#define OBJECT_LIST_WINDOW_H

#include "../../GUI/Window.h"

class Editor;

class ObjectListWindow : public Window {
    public:
    ObjectListWindow(Editor* editor);   //Maybe it would make more sence to supply the Level or the ObjectManager ?

    Editor* m_editor;
};

#endif