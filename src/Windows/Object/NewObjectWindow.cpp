#include "NewObjectWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void CreateNewObjectButton(Button* but) {
    NewObjectWindow* win = (NewObjectWindow*)(but->m_parrent->m_window);

    if(win->m_newobjname.empty() == false) {
        ObjectTemplate* newobj = new ObjectTemplate(win->m_newobjname);
        int err = g_editor->m_level->m_objectmanager->Add(newobj);
        if(err != 0) {
            delete newobj;
        }
    }

    g_editor->m_winmanager->Remove(win);
}

NewObjectWindow::NewObjectWindow() : Window() {
    m_id = WINID_NEWOBJECT;

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = "New object";
    
    m_newobjname = "newobject";
    
    m_height = 60;

    m_widgetmanager->Add(new CppStringField(5, 15, 120, &m_newobjname));
    
    Button* confirmbut = new Button(5, 36, 50, 16);
    confirmbut->SetText("ok");
    confirmbut->SetAction(CreateNewObjectButton);
    m_widgetmanager->Add(confirmbut);
}