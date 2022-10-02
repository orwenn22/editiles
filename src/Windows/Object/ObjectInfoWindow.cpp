#include "ObjectInfoWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringValue.h"
#include "../../GUI/Widget/Label.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../../Widget/ObjectPropertiesList.h"
#include "../WinIDs.h"
#include "RenameObjectWindow.h"
#include "NewPropertyWindow.h"

extern Editor* g_editor;

void DeleteObjectTemplate(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);
    g_editor->m_level->m_objectmanager->Delete(win->m_objptr);

    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
        Window* currentwin = g_editor->m_winmanager->Get(i);
        //TODO : better way to do this ? Only close the windows that contains the pointer to the corresponding object ?
        if(currentwin->m_id >= WINID_RENAMEOBJECT && currentwin->m_id <= WINID_CHANGEPROPERTY) {
            g_editor->m_winmanager->Remove(currentwin);
            i--;
        }
    }

    g_editor->m_winmanager->Remove(win);
}

void OpenRenameWindow(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);

    bool needcreation = true;

    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
        Window* currentwin = g_editor->m_winmanager->Get(i);
        if(currentwin->m_id == WINID_RENAMEOBJECT) {
            if(((RenameObjectWindow*)currentwin)->m_objptr == win->m_objptr) {
                g_editor->m_winmanager->BringOnTop(currentwin);
                needcreation = false;
            }
        }
    }

    if(needcreation) {
        g_editor->m_winmanager->Add(new RenameObjectWindow(g_editor->m_winmanager, win->m_objptr));
    }
}

void OpenNewPropertyWindow(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);

    bool needcreation = true;

    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
        Window* currentwin = g_editor->m_winmanager->Get(i);
        if(currentwin->m_id == WINID_NEWPROPERTY) {
            if(((NewPropertyWindow*)currentwin)->m_objptr == win->m_objptr) {
                g_editor->m_winmanager->BringOnTop(currentwin);
                needcreation = false;
            }
        }
    }
    
    if(needcreation) {
        g_editor->m_winmanager->Add(new NewPropertyWindow(g_editor->m_winmanager, win->m_objptr));
    }
}

ObjectInfoWindow::ObjectInfoWindow(WindowManager* winmanager, ObjectTemplate* objptr) : Window(winmanager) {
    m_id = WINID_OBJECTINFO;
    m_objptr = objptr;

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = TextFormat("Object %p", objptr);

    m_width = 200;
    m_height = 200;

    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 15, "Name :"));
    m_widgetmanager->Add(new CppStringValue(m_widgetmanager, 50, 15, &(m_objptr->m_name)));

    Button* deletebut = new Button(m_widgetmanager, 5, 28, 45, 16);
    deletebut->SetText("Delete");
    deletebut->SetAction(DeleteObjectTemplate);
    m_widgetmanager->Add(deletebut);

    Button* renamebut = new Button(m_widgetmanager, 53, 28, 45, 16);
    renamebut->SetText("Rename");
    renamebut->SetAction(OpenRenameWindow);
    m_widgetmanager->Add(renamebut);

    m_widgetmanager->Add(new ObjectPropertiesList(m_widgetmanager, 5, 50, 190, 120, m_objptr));


    Button* newpropertybut = new Button(m_widgetmanager, 5, 173, 75, 16);
    newpropertybut->SetText("New property");
    newpropertybut->SetAction(OpenNewPropertyWindow);
    m_widgetmanager->Add(newpropertybut);
}