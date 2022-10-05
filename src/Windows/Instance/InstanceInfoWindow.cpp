#include "InstanceInfoWindow.h"

#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Layer/InstanceLayer.h"
#include "../../Layer/Instance.h"
#include "../WinIDs.h"

void Deleteinstance(Button* but) {
    InstanceInfoWindow* win = (InstanceInfoWindow*)(but->m_parrent->m_window);
    win->m_instanceptr->m_parrent->RemoveWithPtr(win->m_instanceptr);
    win->m_parrent->Remove(win);
}

InstanceInfoWindow::InstanceInfoWindow(WindowManager* winmanager, Instance* instranceptr) : Window(winmanager) {
    m_id = WINID_INSTANCEINFO;
    m_instanceptr = instranceptr;

    m_width = 200;
    m_height = 200;

    m_titlebartext = TextFormat("Instance %p", instranceptr);
    m_titlebarcolor = {159, 187, 204, 255};
    m_titlebartextcolor = BLACK;

    Button* deletebut = new Button(m_widgetmanager, 3, 25, 50, 16);
    deletebut->SetText("Delete");
    deletebut->SetAction(Deleteinstance);
    m_widgetmanager->Add(deletebut);
}