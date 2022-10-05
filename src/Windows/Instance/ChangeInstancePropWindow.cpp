#include "ChangeInstancePropWindow.h"

#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/IntField.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Layer/Instance.h"
#include "../../ObjectManager/ObjectProperty.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"

void ChangeInstancePropertyValue(Button* but) {
    ChangeInstancePropWindow* win = (ChangeInstancePropWindow*)(but->m_parrent->m_window);

    int propindex = win->m_instanceptr->m_objtemplateptr->GetPropertyIndex(win->m_propertyptr);

    if(propindex != -1) {   //check if the property was deleted
        if(win->m_propertyptr->type == win->m_proptype) {   //check if the type was changed
            //if all the requirements are met, change the value
            if(win->m_proptype == OPT_INT) {
                win->m_instanceptr->m_properties[propindex].as_int = win->m_intval;
            }
            else if(win->m_proptype == OPT_STR) {
                //copy the string
                int i;
                for(i = 0; i < win->m_strval.length(); i++) {
                    char c = win->m_strval[i];
                    win->m_instanceptr->m_properties[propindex].as_str[i] = c;
                }
                win->m_instanceptr->m_properties[propindex].as_str[i] = 0;  //null-termination
            }
        }
    }

    win->m_parrent->Remove(win);
}

ChangeInstancePropWindow::ChangeInstancePropWindow(WindowManager* winmanager, Instance* instanceptr, ObjectProperty* propertyptr)
: Window(winmanager) {
    m_id = WINID_CHANGEINSTANCEPROP;

    m_instanceptr = instanceptr;
    m_propertyptr = propertyptr;

    //Get the current index of the property in the ObjectTemplate
    //in order to get the value stored in the instance later
    int propindex = m_instanceptr->m_objtemplateptr->GetPropertyIndex(m_propertyptr);

    m_proptype = propertyptr->type;

    m_width = 200;
    m_height = 100;

    m_titlebarcolor = {159, 187, 204, 255};
    m_titlebartextcolor = BLACK;

    if(m_proptype == OPT_INT) {
        m_intval = m_instanceptr->m_properties[propindex].as_int;
        m_widgetmanager->Add(new IntField(m_widgetmanager, 75, 15, 120, &m_intval));
    } 
    else if(m_proptype == OPT_STR) {
        m_strval = m_instanceptr->m_properties[propindex].as_str;
        m_widgetmanager->Add(new CppStringField(m_widgetmanager, 75, 15, 120, &m_strval));
    }


    Button* confirmbut = new Button(m_widgetmanager, 5, 49, 60, 16);
    confirmbut->SetText("Confirm");
    confirmbut->SetAction(ChangeInstancePropertyValue);
    m_widgetmanager->Add(confirmbut);
}