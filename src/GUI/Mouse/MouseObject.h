#ifndef MOUSE_OBJECT_H
#define MOUSE_OBJECT_H

#include "DragAndDropObject.h"

#include <raylib.h>


class Editor;

class MouseObject {
    public:
    MouseObject();
    ~MouseObject();

    //Will update m_x and m_y.
    //Also handle file drag and drop.
    void Update();
    //Clears m_dragobject if left click is released
    void PostUpdate();
    //Does (almost) nothing for now.
    void Draw();

    void GiveDragObject(DragAndDropObject dndobj);

    int m_x;
    int m_y;

    bool m_havebeenused;

    //file drag & drop
    bool m_havefiles;
    FilePathList m_fileslist;

    //elements drag & drop
    bool m_havedragobject;
    DragAndDropObject m_dragobject;
};

extern MouseObject* g_mouse;

MouseObject* InitMouseGlobal();

#endif