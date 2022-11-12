#include "RenamePropertyWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../ObjectManager/ObjectProperty.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void RenameObjectProperty(Button* but) {
    RenamePropertyWindow* win = (RenamePropertyWindow*)(but->m_parrent->m_window);
    printf("rename return code: %i\n", win->m_objptr->RenameProperty(win->m_propptr->name, win->m_newname));
    g_editor->m_winmanager->Remove(win);

}

void DeleteObjectProperty(Button* but) {
    RenamePropertyWindow* win = (RenamePropertyWindow*)(but->m_parrent->m_window);
    win->m_objptr->RemoveProperty(win->m_propptr->name);
    g_editor->m_winmanager->Remove(win);
}

RenamePropertyWindow::RenamePropertyWindow(ObjectTemplate* objptr, ObjectProperty* propptr) : Window() {
    m_id = WINID_RENAMEPROPERTY;

    m_objptr = objptr;
    m_propptr = propptr;

    m_newname = m_propptr->name;

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = TextFormat("Rename prop %p", propptr);

    m_widgetmanager->Add(new CppStringField(5, 15, 60, &m_newname));

    Button* renamebut = new Button(5, 35, 75, 13);
    renamebut->SetText("Confirm");
    renamebut->SetAction(RenameObjectProperty);
    m_widgetmanager->Add(renamebut);

    Button* deletebut = new Button(83, 35, 65, 13);
    deletebut->SetText("Delete");
    deletebut->SetAction(DeleteObjectProperty);
    m_widgetmanager->Add(deletebut);
}