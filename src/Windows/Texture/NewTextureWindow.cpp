#include "NewTextureWindow.h"

#include "../../GUI/Widget/WidgetManager.h"
#include "../../Widget/ImageFileReceiver.h"
#include "../WinIDs.h"

NewTextureWindow::NewTextureWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_NEWTEXTURE;
    m_titlebartext = "New Texture";

    m_titlebarcolor = RED;

    m_width = 82;
    m_height = 94;    

    m_widgetmanager->Add(new ImageFileReceiver(4, 15, 75, 75));
}