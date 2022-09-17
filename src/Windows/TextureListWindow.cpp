#include "TextureListWindow.h"

#include "../Editor.h"
#include "../GUI/Widget/Button.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/WindowManager.h"
#include "../Widget/TextureList.h"
#include "../Windows/NewTextureWindow.h"
#include "WinIDs.h"

extern Editor* g_editor;

void OpenNewTextureWindow(Button*) {
    Window* win = g_editor->m_winmanager->FindWithID(WINID_NEWTEXTURE);
    if(win==NULL) {
        g_editor->m_winmanager->Add(new NewTextureWindow(g_editor->m_winmanager));
    } else {
        g_editor->m_winmanager->BringOnTop(win);
    }
}

TextureListWindow::TextureListWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_TEXTURELIST;
    SetPosition(100, 100);
    
    m_width = 200;
    m_height = 200;

    m_titlebartext = "Texture list";

    m_widgetmanager->Add(new TextureList(m_widgetmanager, 3, 15, 194, 150));

    Button* newbut = new Button(m_widgetmanager, 3, 168, 50, 15);
    newbut->SetText("New");
    newbut->SetAction(OpenNewTextureWindow);
    m_widgetmanager->Add(newbut);
}