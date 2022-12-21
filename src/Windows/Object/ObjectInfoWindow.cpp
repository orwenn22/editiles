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


void DeleteObjectTemplate(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);
    win->m_level->m_objectmanager->Delete(win->m_objptr);

    for(unsigned int i = 0; i < win->m_parrent->m_wincount; i++) {
        Window* currentwin = win->m_parrent->Get(i);
        //TODO : better way to do this ? Only close the windows that contains the pointer to the corresponding object ?
        if(currentwin->m_id >= WINID_RENAMEOBJECT && currentwin->m_id <= WINID_CHANGEPROPERTY) {
            win->m_parrent->Remove(currentwin);
            i--;
        }
    }

    win->m_parrent->Remove(win);
}

void OpenRenameWindow(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);

    bool needcreation = true;

    for(unsigned int i = 0; i < win->m_parrent->m_wincount; i++) {
        Window* currentwin = win->m_parrent->Get(i);
        if(currentwin->m_id == WINID_RENAMEOBJECT) {
            if(((RenameObjectWindow*)currentwin)->m_objptr == win->m_objptr) {
                win->m_parrent->BringOnTop(currentwin);
                needcreation = false;
            }
        }
    }

    if(needcreation) {
        win->m_parrent->Add(new RenameObjectWindow(win->m_objptr));
    }
}

void OpenNewPropertyWindow(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);

    bool needcreation = true;

    for(unsigned int i = 0; i < win->m_parrent->m_wincount; i++) {
        Window* currentwin = win->m_parrent->Get(i);
        if(currentwin->m_id == WINID_NEWPROPERTY) {
            if(((NewPropertyWindow*)currentwin)->m_objptr == win->m_objptr) {
                win->m_parrent->BringOnTop(currentwin);
                needcreation = false;
            }
        }
    }
    
    if(needcreation) {
        win->m_parrent->Add(new NewPropertyWindow(win->m_objptr));
    }
}

void ExportObjectAsFile(Button* but) {
    ObjectInfoWindow* win = (ObjectInfoWindow*)(but->m_parrent->m_window);

    win->m_objptr->SaveStandalone(win->m_objptr->m_name + ".obj");
}

ObjectInfoWindow::ObjectInfoWindow(ObjectTemplate* objptr, Editor* editor) : Window() {
    m_level = editor->m_level;

    m_id = WINID_OBJECTINFO;
    m_objptr = objptr;

    m_titlebarcolor = {46, 41, 78, 255};
    m_titlebartext = TextFormat("Object %p", objptr);

    m_width = 200;
    m_height = 200;

    m_widgetmanager->Add(new Label(5, 15, "Name :"));
    m_widgetmanager->Add(new CppStringValue(50, 15, &(m_objptr->m_name)));

    Button* deletebut = new Button(5, 28, 45, 16);
    deletebut->SetText("Delete");
    deletebut->SetAction(DeleteObjectTemplate);
    m_widgetmanager->Add(deletebut);

    Button* renamebut = new Button(53, 28, 45, 16);
    renamebut->SetText("Rename");
    renamebut->SetAction(OpenRenameWindow);
    m_widgetmanager->Add(renamebut);


    m_widgetmanager->Add(new ObjectPropertiesList(5, 50, 190, 120, m_objptr, editor));


    Button* newpropertybut = new Button(5, 173, 75, 16);
    newpropertybut->SetText("New property");
    newpropertybut->SetAction(OpenNewPropertyWindow);
    m_widgetmanager->Add(newpropertybut);


    Button* exoprtbut = new Button(90, 173, 75, 16);
    exoprtbut->SetText("Export");
    exoprtbut->SetAction(ExportObjectAsFile);
    m_widgetmanager->Add(exoprtbut);
}