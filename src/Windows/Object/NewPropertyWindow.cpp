#include "NewPropertyWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../ObjectManager/ObjectProperty.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void CreateNewProperty(Button* but) {
    NewPropertyWindow* win = (NewPropertyWindow*)(but->m_parrent->m_window);

    ObjectProperty* newprop = new ObjectProperty(win->m_newpropertyname);

    if(win->m_objptr->AddProperty(newprop) == 1) {  //adding property failed
        delete newprop;
    }

    g_editor->m_winmanager->Remove(win);
}


NewPropertyWindow::NewPropertyWindow(WindowManager* winmanager, ObjectTemplate* objptr) : Window(winmanager) {
    m_id = WINID_NEWPROPERTY;
    m_objptr = objptr;

    m_newpropertyname = "property";

    m_titlebartext = "New prop";

    m_widgetmanager->Add(new CppStringField(m_widgetmanager, 5, 15, 75, &m_newpropertyname));

    Button* confirmbut = new Button(m_widgetmanager, 5, 32, 50, 16);
    confirmbut->SetText("Create");
    confirmbut->SetAction(CreateNewProperty);
    m_widgetmanager->Add(confirmbut);
}