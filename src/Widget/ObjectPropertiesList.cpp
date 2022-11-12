#include "ObjectPropertiesList.h"

#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/WindowManager.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../Windows/Object/ChangePropertyWindow.h"
#include "../Windows/Object/RenamePropertyWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>

extern Editor* g_editor;

ObjectPropertiesList::ObjectPropertiesList(int x, int y, int w, int h, ObjectTemplate* objptr) : ElementList(x, y, w, h) {
    m_objptr = objptr;
    m_elementheight = 15;
    m_canselectelement = false;
    m_firstelementindex = 0;
}



int ObjectPropertiesList::GetElementCount() {
    return m_objptr->m_propertycount;
}

void ObjectPropertiesList::DrawElement(int painterx, int paintery, int elementindex) {
    int separatorx = m_width/2;

    ObjectProperty* prop = m_objptr->GetProperty(elementindex);

    //vertical separator
    DrawLine(painterx+separatorx, paintery+1, painterx+separatorx, paintery+m_elementheight, GRAY);

    //Draw property name
    if(prop->obligatory) {
        DrawText(prop->name.c_str(), painterx+3, paintery+2, 10, GRAY);
    }
    else {
        DrawText(prop->name.c_str(), painterx+3, paintery+2, 10, WHITE);
    }

    //Draw property default value
    if(prop->havedefaultvalue == false) {
        DrawText("X", painterx + separatorx + 3, paintery+2, 10, RED);
    }
    else {
        if(prop->type == OPT_INT) {
            DrawText(TextFormat("%i", prop->defaultvalue.as_int), painterx + separatorx + 3, paintery+2, 10, WHITE);
        } else if(prop->type == OPT_STR) {
            DrawText(TextFormat("%s", prop->defaultvalue.as_str), painterx + separatorx + 3, paintery+2, 10, WHITE);
        }
    }
}

void ObjectPropertiesList::RightClickOn(int elementindex) {
    int separatorx = m_width/2;

    ObjectProperty* prop = m_objptr->GetProperty(elementindex);

    if(g_mouse->m_x < m_x+separatorx) {     //rename property
        if(prop->obligatory == false) {
            bool needcreation = true;
            for(unsigned int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
                Window* win = g_editor->m_winmanager->Get(i);

                if(win->m_id == WINID_RENAMEPROPERTY) {
                    if(((RenamePropertyWindow*)win)->m_propptr == prop) {   //window already exist
                        needcreation = false;
                        g_editor->m_winmanager->BringOnTop(win);
                        break;
                    }
                }
            }
            if(needcreation) {
                g_editor->m_winmanager->Add(new RenamePropertyWindow(g_editor->m_winmanager, m_objptr, prop));
            }
        }
        
    } else {                //change value
        if(prop->havedefaultvalue) {
            bool needcreation = true;
            for(unsigned int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
                Window* win = g_editor->m_winmanager->Get(i);

                if(win->m_id == WINID_CHANGEPROPERTY) {
                    if(((ChangePropertyWindow*)win)->m_propptr == prop) {   //window already exist
                        needcreation = false;
                        g_editor->m_winmanager->BringOnTop(win);
                        break;
                    }
                }
            }
            if(needcreation) {
                g_editor->m_winmanager->Add(new ChangePropertyWindow(g_editor->m_winmanager, prop, m_objptr));
            }
        }
        
    }
}