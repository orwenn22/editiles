#include "Application.h"

#include "Editor.h"
#include "GUI/BottomBar.h"
#include "GUI/Mouse/MouseObject.h"
#include "GUI/Themes/ColorTheme.h"
#include "GUI/WindowCorner.h"
#include "GUI/WindowManager.h"
#include "Windows/NewLevelWindow.h"
#include "Windows/WinIDs.h"

#include "GUI/TabBar.h"
#include "EditorTabsHandler.h"

Application::Application() {
    m_tabshandler = new EditorTabsHandler(this);

    m_mouse = InitMouseGlobal();
    m_corner = new WindowCorner(500, 500);
    m_bottombar = new BottomBar();
    m_winmanager = new WindowManager();
    m_tabbar = new TabBar(m_tabshandler);

    
    m_editorcount = 0;
    m_currenteditor = -1;
}

Application::~Application() {
    for(Editor* e : m_editors) {
        delete e;
    }
    m_editors.clear();
    m_editorcount = 0;

    delete m_winmanager;

    delete m_bottombar;
    delete m_corner;
    delete m_tabbar;
    delete m_mouse;

    delete m_tabshandler;
}


void Application::Update() {
    KeyBindsUpdate();

    m_mouse->Update();

    m_corner->Update();
    m_bottombar->Update();
    m_winmanager->Update();
    m_tabbar->Update();



    m_currenteditor += (IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT));

    UpdateEditor();

    m_mouse->PostUpdate();
}

void Application::UpdateEditor() {
    if(m_editorcount <= 0) return;

    if(m_currenteditor < 0) m_currenteditor = 0;
    else if(m_currenteditor >= m_editorcount) m_currenteditor = m_editorcount - 1;


    m_editors[m_currenteditor]->Update();
}



void Application::Draw() {
    ClearBackground(g_colortheme->Background);

    DrawEditor();

    m_tabbar->Draw();
    m_winmanager->Draw();
    m_bottombar->Draw();
    m_corner->Draw();

    m_mouse->Draw();
}

void Application::DrawEditor() {
    if(m_editorcount <= 0) {
        DrawText("No editor open :(", 5, 100, 10, GRAY);
        return;
    }

    if(m_currenteditor < 0) m_currenteditor = 0;
    else if(m_currenteditor >= m_editorcount) m_currenteditor = m_editorcount - 1;

    m_editors[m_currenteditor]->Draw();
}


void Application::AddEditor(Editor* editor) {
    m_editors.push_back(editor);
    m_editorcount++;

    editor->m_app = this;
}

void Application::RemoveEditor(int index) {
    if(index >= 0 && index < m_editorcount) {
        delete m_editors[index];
        m_editors.erase(m_editors.begin() + index);
        m_editorcount--;
    }
}

std::string Application::GetEditorName(int index) {
    if(index >= 0 && index < m_editorcount) {
        return m_editors[index]->m_name;
    }
    return "NO INDEX";
}

void Application::LoadFile(std::string filename) {
    Editor* neweditor = new Editor(filename.c_str());

    if(neweditor->m_havelevel) AddEditor(neweditor);
    else delete neweditor;

}

void Application::KeyBindsUpdate() {
    if(IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_N)) {                   //NEW LEVEL WINDOW
        OpenNewLevelWindow();
    }
}

void Application::OpenNewLevelWindow() {
    Window* winptr = m_winmanager->FindWithID(WINID_NEWLEVEL);
    if(winptr == NULL) {
        m_winmanager->Add(new NewLevelWindow(this));
    }
    else {
        m_winmanager->BringOnTop(winptr);
    }
}