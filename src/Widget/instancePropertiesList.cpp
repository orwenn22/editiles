#include "InstancePropertiesList.h"

#include "../Editor.h"
#include "../GUI/WindowManager.h"
#include "../Layer/Instance.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../Windows/Instance/ChangeInstancePropWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>

extern Editor* g_editor;

InstancePropertiesList::InstancePropertiesList(WidgetManager* widgetmanager, Instance* instanceptr, int x, int y, int w, int h)
: ElementList(widgetmanager, x, y, w, h) {
    m_instanceptr = instanceptr;
    m_elementheight = 15;
    m_canselectelement = false;
}

int InstancePropertiesList::GetElementCount() {
    return m_instanceptr->m_objtemplateptr->m_propertycount;
}

void InstancePropertiesList::DrawElement(int painterx, int paintery, int elementindex) {
    int xcenter = m_width / 2;
    ObjectProperty* propintemplate = m_instanceptr->m_objtemplateptr->GetProperty(elementindex);
    
    DrawText(propintemplate->name.c_str() ,painterx + 2, paintery + 2, 10, WHITE);

    DrawLine(painterx + xcenter, paintery, painterx + xcenter, paintery + m_elementheight, GRAY);

    if(propintemplate->type == OPT_INT) {
        DrawText(TextFormat("%i", m_instanceptr->m_properties[elementindex].as_int), painterx + xcenter + 2, paintery + 2, 10, WHITE);
    }
    else if(propintemplate->type == OPT_STR) {
        DrawText(m_instanceptr->m_properties[elementindex].as_str, painterx + xcenter + 2, paintery + 2, 10, WHITE);
    }
}

void InstancePropertiesList::RightClickOn(int elementindex) {
    ObjectProperty* propintemplate = m_instanceptr->m_objtemplateptr->GetProperty(elementindex);

    bool needcreation = true;
    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
        printf("%i\n", i);
        Window* win = g_editor->m_winmanager->Get(i);
        if(win->m_id == WINID_CHANGEINSTANCEPROP) {
            if(((ChangeInstancePropWindow*)win)->m_instanceptr == m_instanceptr && ((ChangeInstancePropWindow*)win)->m_propertyptr == propintemplate) {
                g_editor->m_winmanager->BringOnTop(win);
                needcreation = false;
                break;
            }
        }
    }

    if(needcreation) {
        g_editor->m_winmanager->Add(new ChangeInstancePropWindow(g_editor->m_winmanager, m_instanceptr, propintemplate));
    }
}