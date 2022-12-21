#include "TextureListWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Widget/TextureList.h"
#include "../WinIDs.h"
#include "NewTextureWindow.h"

void OpenNewTextureWindow(Button* but) {
    TextureListWindow* textlistwin = (TextureListWindow*) but->m_parrent->m_window; 
    Editor* editor = textlistwin->m_editor;

    Window* win = editor->m_winmanager->FindWithID(WINID_NEWTEXTURE);
    if(win==NULL) {
        editor->m_winmanager->Add(new NewTextureWindow(editor));
    } else {
        editor->m_winmanager->BringOnTop(win);
    }
}

TextureListWindow::TextureListWindow(Editor* editor) : Window() {
    m_editor = editor;

    m_id = WINID_TEXTURELIST;
    SetPosition(100, 100);
    
    m_width = 200;
    m_height = 200;

    m_titlebarcolor = RED;
    m_titlebartext = "Texture list";

    m_widgetmanager->Add(new TextureList(3, 15, 194, 150, m_editor));

    Button* newbut = new Button(3, 168, 50, 15);
    newbut->SetText("New");
    newbut->SetAction(OpenNewTextureWindow);
    m_widgetmanager->Add(newbut);
}