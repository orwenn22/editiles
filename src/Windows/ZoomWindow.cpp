#include "ZoomWindow.h"

#include "../Editor.h"
#include "../GUI/MainWindow.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/Widget/Button.h"
#include "../Level.h"
#include "WinIDs.h"


void ZoomIn(Button* but) {
    ZoomWindow* win = (ZoomWindow*) but->m_parrent->m_window;
    win->m_editor->Zoom(1, g_winwidth / 2, g_winheight / 2);
}

void ZoomOut(Button* but) {
    ZoomWindow* win = (ZoomWindow*) but->m_parrent->m_window;
    win->m_editor->Zoom(-1, g_winwidth / 2, g_winheight / 2);
}

ZoomWindow::ZoomWindow(Editor* editor) : Window() {
    m_editor = editor;

    SetPosition(100, 100);
    m_id = WINID_ZOOM;

    m_width = 120;
    m_height = 54;

    m_titlebartext = "Zoom";
    m_titlebarcolor = RED;

    Button* zoomintbutton = new Button(3, 16, 114, 15);
    zoomintbutton->SetText("Zoom in");
    zoomintbutton->SetAction(ZoomIn);
    m_widgetmanager->Add(zoomintbutton);

    Button* zoomoutbutton = new Button(3, 36, 114, 15);
    zoomoutbutton->SetText("Zoom out");
    zoomoutbutton->SetAction(ZoomOut);
    m_widgetmanager->Add(zoomoutbutton);

}