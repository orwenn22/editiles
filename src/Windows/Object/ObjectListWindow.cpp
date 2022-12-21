#include "ObjectListWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../Widget/ObjectList.h"
#include "../WinIDs.h"
#include "NewObjectWindow.h"


void NewObjectButtonAction(Button* but) {
    ObjectListWindow* win = (ObjectListWindow*) but->m_parrent->m_window;
    Editor* editor = win->m_editor;

    //Open the object creation window. (or bring it on top if it already exists)
    Window* newobjwinptr = editor->m_winmanager->FindWithID(WINID_NEWOBJECT);
    if(newobjwinptr == NULL) {
        editor->m_winmanager->Add(new NewObjectWindow(editor->m_level->m_objectmanager));
    }
    else {
        editor->m_winmanager->BringOnTop(newobjwinptr);
    }
}

void ExportObjectListButtonAction(Button* but) {
    ObjectListWindow* win = (ObjectListWindow*) but->m_parrent->m_window;
    Editor* editor = win->m_editor;

    editor->m_level->m_objectmanager->SaveStandalone();
}

ObjectListWindow::ObjectListWindow(Editor* editor) : Window() {
    m_editor = editor;

    m_id = WINID_OBJECTLIST;
    SetPosition(100, 100);

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = "Object list";

    m_width = 200;
    m_height = 200;

    m_widgetmanager->Add(new ObjectList(3, 15, 194, 150, editor));

    Button* newbut = new Button(3, 168, 50, 15);
    newbut->SetText("New");
    newbut->SetAction(NewObjectButtonAction);
    m_widgetmanager->Add(newbut);

    Button* exportbut = new Button(58, 168, 50, 15);
    exportbut->SetText("Export");
    exportbut->SetAction(ExportObjectListButtonAction);
    m_widgetmanager->Add(exportbut);
}