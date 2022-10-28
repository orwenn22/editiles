#include "MouseObject.h"

#include <raylib.h>
#include <stdio.h>

//global mouse
MouseObject* g_mouse;

MouseObject::MouseObject() {
    m_havebeenused = false;

    m_havefiles = false;
    m_fileslist = { 0, 0, 0 };

    m_havedragobject = false;
    m_dragobject = DragAndDropObject();
}

MouseObject::~MouseObject() {
    UnloadDroppedFiles(m_fileslist);
}

void MouseObject::Update() {
    m_havefiles = false;
    if(IsFileDropped()) {
        m_havefiles = true;

        if (m_fileslist.count > 0) UnloadDroppedFiles(m_fileslist);

        m_fileslist = LoadDroppedFiles();
    }
    m_havebeenused = false;
    m_x = GetMouseX();
    m_y = GetMouseY();
}

void MouseObject::PostUpdate() {
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && m_havedragobject) {
        m_havedragobject = false;
        m_dragobject = DragAndDropObject();
    }
}

void MouseObject::Draw() {
    if(m_havedragobject) {
        DrawText(m_dragobject.m_text.c_str(), m_x, m_y, 10, WHITE);
    }
}

void MouseObject::GiveDragObject(DragAndDropObject dndobj) {
    m_havedragobject = true;
    m_dragobject = dndobj;
}

MouseObject* InitMouseGlobal() {
    g_mouse = new MouseObject();
    return g_mouse;
}