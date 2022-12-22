#include "Application.h"

#include "Editor.h"
#include "GUI/BottomBar.h"
#include "GUI/Mouse/MouseObject.h"
#include "GUI/WindowCorner.h"
#include "GUI/WindowManager.h"

Application::Application() {
    m_mouse = InitMouseGlobal();
    m_corner = new WindowCorner(500, 500);
    m_bottombar = new BottomBar();
    m_winmanager = new WindowManager();

    m_editor = new Editor();
}

Application::~Application() {
    delete m_editor;
    delete m_winmanager;

    delete m_bottombar;
    delete m_corner;
    delete m_mouse;
}


void Application::Update() {
    m_mouse->Update();
    m_corner->Update();
    m_bottombar->Update();

    m_winmanager->Update();
    m_editor->Update();

    m_mouse->PostUpdate();
}

void Application::Draw() {
    m_editor->Draw();
    m_winmanager->Draw();

    m_bottombar->Draw();
    m_corner->Draw();
    m_mouse->Draw();
}


void Application::AddEditor(Editor* editor) {
    m_editor = editor;
    m_editor->m_app = this;
}