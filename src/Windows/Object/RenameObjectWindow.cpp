#include "RenameObjectWindow.h"

#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"


void RenameObjectTemplate(Button* but) {
    RenameObjectWindow* win = (RenameObjectWindow*)(but->m_parrent->m_window);
    if(win->m_newname.empty() == false) {
        win->m_objptr->m_manager->RenameObject(win->m_objptr->m_name, win->m_newname);
    }
    win->m_parrent->Remove(win);
}

RenameObjectWindow::RenameObjectWindow(ObjectTemplate* objptr) : Window() {
    m_id = WINID_RENAMEOBJECT;

    m_objptr = objptr;
    m_newname = objptr->m_name;

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = "Rename object";

    m_widgetmanager->Add(new CppStringField(5, 15, 60, &m_newname));

    Button* renamebut = new Button(5, 35, 75, 13);
    renamebut->SetText("Confirm");
    renamebut->SetAction(RenameObjectTemplate);
    m_widgetmanager->Add(renamebut);
}