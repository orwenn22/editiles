#include "ChangePropertyWindow.h"

#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/IntField.h"
#include "../../GUI/Widget/Label.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../ObjectManager/ObjectProperty.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"

void ChangePropertyDefaultValueint(Button* but) {
    ChangePropertyWindow* win = (ChangePropertyWindow*) but->m_parrent->m_window;
    win->m_objptr->SetPropertyValue(win->m_propptr->name, win->m_intval);
    win->m_parrent->Remove(win);
}

void ChangePropertyDefaultValuestring(Button* but) {
    ChangePropertyWindow* win = (ChangePropertyWindow*) but->m_parrent->m_window;
    win->m_objptr->SetPropertyValue(win->m_propptr->name, win->m_strval);
    win->m_parrent->Remove(win);
}

ChangePropertyWindow::ChangePropertyWindow(WindowManager* winmanager, ObjectProperty* propptr, ObjectTemplate* objptr) : Window(winmanager) {
    m_id = WINID_CHANGEPROPERTY;
    
    m_width = 200;
    m_height = 100;

    m_propptr = propptr;
    m_objptr = objptr;

    m_intval = 0;
    m_strval = "";

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = TextFormat("Change prop value %p", m_propptr);

    if(m_propptr->type == OPT_INT) {
        m_intval = m_propptr->defaultvalue.as_int;
    } 
    else if(m_propptr->type == OPT_STR) {
        m_strval = m_propptr->defaultvalue.as_str;
    }

    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 15, "int :"));
    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 32, "str :"));

    m_widgetmanager->Add(new IntField(m_widgetmanager, 75, 15, 120, &m_intval));
    m_widgetmanager->Add(new CppStringField(m_widgetmanager, 75, 32, 120, &m_strval));

    Button* confirmint = new Button(m_widgetmanager, 5, 49, 60, 16);
    confirmint->SetText("Confirm int");
    confirmint->SetAction(ChangePropertyDefaultValueint);
    m_widgetmanager->Add(confirmint);

    Button* confirmstr = new Button(m_widgetmanager, 5, 67, 60, 16);
    confirmstr->SetText("Confirm str");
    confirmstr->SetAction(ChangePropertyDefaultValuestring);
    m_widgetmanager->Add(confirmstr);
}