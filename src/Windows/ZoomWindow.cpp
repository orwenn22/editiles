#include "ZoomWindow.h"

#include "../GUI/MainWindow.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/Widget/Button.h"
#include "../Editor.h"
#include "../Level.h"
#include "../Zoom.h"
#include "WinIDs.h"

extern Editor* g_editor;


void ZoomIn(Button*) {
    Zoom(1, g_winwidth / 2, g_winheight / 2);
}

void ZoomOut(Button*) {
    Zoom(-1, g_winwidth / 2, g_winheight / 2);
}

ZoomWindow::ZoomWindow() : Window() {
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