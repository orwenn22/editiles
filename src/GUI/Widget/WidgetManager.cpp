#include "WidgetManager.h"

#include "Widget.h"
#include "../Window.h"

WidgetManager::WidgetManager(Window* win) {
    m_window = win;
    m_isinwindow = true;
    m_count = 0;

    m_baseposx = m_window->m_x;
    m_baseposy = m_window->m_y;
}

WidgetManager::WidgetManager() {
    m_isinwindow = false;
    m_count = 0;

    m_baseposx = 0;
    m_baseposy = 0;
}

WidgetManager::~WidgetManager() {
    for(int i = 0; i < m_count; i++) {
        delete m_widgets[i];
    }
    m_count = 0;
}

void WidgetManager::Update() {
    for(int i = 0; i < m_count; i++) {
        m_widgets[i]->Update();
    }
}

void WidgetManager::ChangeBasePos(int x, int y) {
    m_baseposx = x;
    m_baseposy = y;
    UpdateAllPos();
}

void WidgetManager::UpdateAllPos() {
    for(int i = 0; i < m_count; i++) {
        m_widgets[i]->UpdatePos();
    }
}

void WidgetManager::Draw() {
    for(int i = m_count - 1; i >= 0; i--) {
        m_widgets[i]->Draw();
    }
}

void WidgetManager::Add(Widget* newwidget) {
    m_widgets.push_back(newwidget);
    m_count++;
}

void WidgetManager::Remove(Widget* widgetptr) {
    for(int i = 0; i < m_count; i++) {
        if(m_widgets[i] == widgetptr) {
            m_widgets.erase(m_widgets.begin() + i);
            delete widgetptr;
            m_count--;
            return;
        }
    }
}