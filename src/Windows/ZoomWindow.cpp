#include "ZoomWindow.h"

#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/Widget/Button.h"
#include "../Editor.h"
#include "../Level.h"
#include "../Zoom.h"
#include "WinIDs.h"

extern int g_winwidth;
extern int g_winheight;
extern Editor* g_editor;

//todo : choose better name ?
/*
void Zoom(int relativezoom) {
    //calculate middle of screen
    int midwidth = g_winwidth / 2;
    int midheight = g_winheight / 2;

    //calculate distance between middle of window and top left of grid
    int xdist = g_editor->m_level->m_x - midwidth;
    int ydist = g_editor->m_level->m_y - midheight;

    //calculate the number of box for that distance
    float xboxcount = (float)xdist / (float)(g_editor->m_level->m_boxwidth * g_editor->m_level->m_zoom);
    float yboxcount = (float)ydist / (float)(g_editor->m_level->m_boxheight * g_editor->m_level->m_zoom);

    //calculate the new distance with the new zoom level
    float newxdist = xboxcount * (float)(g_editor->m_level->m_boxwidth * (g_editor->m_level->m_zoom+relativezoom));
    float newydist = yboxcount * (float)(g_editor->m_level->m_boxheight * (g_editor->m_level->m_zoom+relativezoom));

    //apply new distance
    g_editor->m_level->m_x = midwidth + (int)newxdist;
    g_editor->m_level->m_y = midheight + (int)newydist;

    g_editor->m_level->m_zoom += relativezoom;
}
*/


void ZoomIn(Button*) {
    Zoom(1, g_winwidth / 2, g_winheight / 2);
}

void ZoomOut(Button*) {
    Zoom(-1, g_winwidth / 2, g_winheight / 2);
}

ZoomWindow::ZoomWindow(WindowManager* wm) : Window(wm) {
    SetPosition(100, 100);
    m_id = WINID_ZOOM;

    m_width = 120;
    m_height = 54;

    m_titlebartext = "Zoom";
    m_titlebarcolor = RED;

    Button* zoomintbutton = new Button(m_widgetmanager, 3, 16, 114, 15);
    zoomintbutton->SetText("Zoom in");
    zoomintbutton->SetAction(ZoomIn);
    m_widgetmanager->Add(zoomintbutton);

    Button* zoomoutbutton = new Button(m_widgetmanager, 3, 36, 114, 15);
    zoomoutbutton->SetText("Zoom out");
    zoomoutbutton->SetAction(ZoomOut);
    m_widgetmanager->Add(zoomoutbutton);

}