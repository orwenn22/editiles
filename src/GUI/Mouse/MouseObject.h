#ifndef MOUSE_OBJECT_H
#define MOUSE_OBJECT_H

#include "DragAndDropObject.h"

#include <raylib.h>


class Editor;

class MouseObject {
    public:
    MouseObject();
    ~MouseObject();

    void Update();
    void PostUpdate();
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

#endif