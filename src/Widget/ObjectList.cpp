#include "ObjectList.h"

#include "../Editor.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../ObjectManager/ObjectManager.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../Windows/Object/ObjectInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>

extern Editor* g_editor;

ObjectList::ObjectList(WidgetManager* widgetmanager, int x, int y, int w, int h) : ElementList(widgetmanager, x, y, w, h) {
    m_elementheight = 30;
    m_canselectelement = false;
}

void ObjectList::RightClickOn(int clickindex) {
    ObjectTemplate* objptr = g_editor->m_level->m_objectmanager->Get(clickindex);
    bool needcreation = true;

    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
        Window* win = g_editor->m_winmanager->Get(i);
        if(win->m_id == WINID_OBJECTINFO) {
            if(((ObjectInfoWindow*)win)->m_objptr == objptr) {
                needcreation = false;
                g_editor->m_winmanager->BringOnTop(win);
            }
        }
    }

    if(needcreation) {
        g_editor->m_winmanager->Add(new ObjectInfoWindow(g_editor->m_winmanager, objptr));
    }
}

void ObjectList::DrawElement(int painterx, int paintery, int elementindex) {
    DrawText(g_editor->m_level->m_objectmanager->Get(elementindex)->m_name.c_str(), painterx+3, paintery+10, 10, WHITE);
}

int ObjectList::GetElementCount() {
    return g_editor->m_level->m_objectmanager->m_objectcount;
}