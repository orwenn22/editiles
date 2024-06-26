#include "InstancePropertiesList.h"

#include "../Editor.h"
#include "../GUI/Themes/ColorTheme.h"
#include "../GUI/WindowManager.h"
#include "../Layer/Instance.h"
#include "../Layer/InstanceLayer.h"
#include "../Level.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../Windows/Instance/ChangeInstancePropWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>


InstancePropertiesList::InstancePropertiesList(Instance* instanceptr, int x, int y, int w, int h) : ElementList(x, y, w, h) {
    m_instanceptr = instanceptr;
    m_elementheight = 15;
    m_canselectelement = false;

    //Get a pointer to the editor from the instance.
    //            instance      layer      level     editor
    m_editor = m_instanceptr->m_parrent->m_parrent->m_editor;
}

int InstancePropertiesList::GetElementCount() {
    return m_instanceptr->m_objtemplateptr->m_propertycount;
}

//Display one property and its corresponding value
void InstancePropertiesList::DrawElement(int painterx, int paintery, int elementindex) {
    int xcenter = m_width / 2;

    //Get the property that is being drawn
    ObjectProperty* property = m_instanceptr->GetProperty(elementindex);
    
    //Display the name of the property at the left
    DrawText(property->name.c_str() ,painterx + 2, paintery + 2, 10, g_colortheme->TextColor);

    //Separator in the middle
    DrawLine(painterx + xcenter, paintery, painterx + xcenter, paintery + m_elementheight, g_colortheme->OutlineSecondary);

    //Display the value of the property on the right
    if(property->type == OPT_INT) {
        DrawText(TextFormat("%i", m_instanceptr->m_properties[elementindex].as_int), painterx + xcenter + 2, paintery + 2, 10, g_colortheme->TextColor);
    }
    else if(property->type == OPT_STR) {
        DrawText(m_instanceptr->m_properties[elementindex].as_str, painterx + xcenter + 2, paintery + 2, 10, g_colortheme->TextColor);
    }
}

void InstancePropertiesList::RightClickOn(int elementindex) {
    //Get the clicked property
    ObjectProperty* property = m_instanceptr->GetProperty(elementindex);

    //Show the window to change the property.
    bool needcreation = true;
    for(unsigned int i = 0; i < m_editor->m_winmanager->GetWindowCount(); i++) {
        printf("%i\n", i);
        Window* win = m_editor->m_winmanager->Get(i);
        if(win->m_id == WINID_CHANGEINSTANCEPROP) {
            if(((ChangeInstancePropWindow*)win)->m_instanceptr == m_instanceptr && ((ChangeInstancePropWindow*)win)->m_propertyptr == property) {
                m_editor->m_winmanager->BringOnTop(win);
                needcreation = false;
                break;
            }
        }
    }

    if(needcreation) {
        m_editor->m_winmanager->Add(new ChangeInstancePropWindow(m_instanceptr, property));
    }
}