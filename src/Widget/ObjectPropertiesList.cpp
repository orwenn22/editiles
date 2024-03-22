#include "ObjectPropertiesList.h"

#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Themes/ColorTheme.h"
#include "../GUI/WindowManager.h"
#include "../ObjectManager/ObjectManager.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../Windows/Object/ChangePropertyWindow.h"
#include "../Windows/Object/RenamePropertyWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>


ObjectPropertiesList::ObjectPropertiesList(int x, int y, int w, int h, ObjectTemplate* objptr, Editor* editor) : ElementList(x, y, w, h) {
    m_objptr = objptr;
    m_elementheight = 15;
    m_canselectelement = false;
    m_firstelementindex = 0;

    m_editor = editor;
}



int ObjectPropertiesList::GetElementCount() {
    return m_objptr->m_propertycount;
}

void ObjectPropertiesList::DrawElement(int painterx, int paintery, int elementindex) {
    int separatorx = m_width/2;

    ObjectProperty* prop = m_objptr->GetProperty(elementindex);

    //vertical separator
    DrawLine(painterx+separatorx, paintery+1, painterx+separatorx, paintery+m_elementheight, g_colortheme->OutlineSecondary);

    //Draw property name
    if(prop->obligatory) {
        DrawText(prop->name.c_str(), painterx+3, paintery+2, 10, g_colortheme->OutlineSecondary);
    }
    else {
        DrawText(prop->name.c_str(), painterx+3, paintery+2, 10, g_colortheme->TextColor);
    }

    //Draw property default value
    if(prop->havedefaultvalue == false) {
        DrawText("X", painterx + separatorx + 3, paintery+2, 10, RED);
    }
    else {
        if(prop->type == OPT_INT) {
            DrawText(TextFormat("%i", prop->defaultvalue.as_int), painterx + separatorx + 3, paintery+2, 10, g_colortheme->TextColor);
        } else if(prop->type == OPT_STR) {
            DrawText(TextFormat("%s", prop->defaultvalue.as_str), painterx + separatorx + 3, paintery+2, 10, g_colortheme->TextColor);
        }
    }
}

void ObjectPropertiesList::RightClickOn(int elementindex) {
    int separatorx = m_width/2;

    ObjectProperty* prop = m_objptr->GetProperty(elementindex);

    if(g_mouse->m_x < m_x+separatorx) {     //rename property
        if(prop->obligatory == false) {
            bool needcreation = true;
            for(unsigned int i = 0; i < m_editor->m_winmanager->GetWindowCount(); i++) {
                Window* win = m_editor->m_winmanager->Get(i);

                if(win->m_id == WINID_RENAMEPROPERTY) {
                    if(((RenamePropertyWindow*)win)->m_propptr == prop) {   //window already exist
                        needcreation = false;
                        m_editor->m_winmanager->BringOnTop(win);
                        break;
                    }
                }
            }
            if(needcreation) {
                m_editor->m_winmanager->Add(new RenamePropertyWindow(m_objptr, prop));
            }
        }
        
    } else {                //change value
        if(prop->havedefaultvalue) {
            bool needcreation = true;
            for(unsigned int i = 0; i < m_editor->m_winmanager->GetWindowCount(); i++) {
                Window* win = m_editor->m_winmanager->Get(i);

                if(win->m_id == WINID_CHANGEPROPERTY) {
                    if(((ChangePropertyWindow*)win)->m_propptr == prop) {   //window already exist
                        needcreation = false;
                        m_editor->m_winmanager->BringOnTop(win);
                        break;
                    }
                }
            }
            if(needcreation) {
                m_editor->m_winmanager->Add(new ChangePropertyWindow(prop, m_objptr));
            }
        }
        
    }
}