#include "Window.h"

#include "../Editor.h"
#include "Mouse/MouseObject.h"
#include "Widget/IntField.h"
#include "Widget/WidgetManager.h"
#include "Widget/Widget.h"
#include "WindowManager.h"

#include <stdio.h>

#include <raylib.h>

extern Editor* g_editor;
extern MouseObject* g_mouse;

extern int g_winwidth;
extern int g_winheight;


Window::Window(WindowManager* winmanager) {
    m_parrent = winmanager;

    m_x = 50;
    m_y = 50;

    m_width = 150;
    m_height = 50;

    m_followmouse = false;

    m_titlebarcolor = BLUE;
    m_titlebartextcolor = WHITE;
    m_titlebartext = "Window";
    m_id = 0;
    
    m_widgetmanager = new WidgetManager(this);
}

Window::~Window() {
    delete m_widgetmanager;
    printf("Destroyed Window\n");
}

void Window::MUpdate() {
    if(PreUpdate()) {
        return;
    }
    Update();
    PostUpdate();
}

bool Window::PreUpdate() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x + m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y + m_height) {  //on window
            m_parrent->BringOnTop(this);

            if(g_mouse->m_y >= m_y && g_mouse->m_y < m_y + 15) {    //on title bar
                if(g_mouse->m_x >= m_x + m_width - 12) {                      //on close button
                    g_mouse->m_havebeenused = true;
                    m_parrent->Remove(this);
                    return true;
                }

                m_followmouse = true;
                m_xmouseoffset = m_x - g_mouse->m_x;
                m_ymouseoffset = m_y - g_mouse->m_y;
            }
        }
    }

    if(m_followmouse) {
        m_x = g_mouse->m_x + m_xmouseoffset;
        m_y = g_mouse->m_y + m_ymouseoffset;
    
        m_widgetmanager->UpdateAllPos();
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_followmouse = false;
    }


    //The subwindow can't go outside the visible space of the big window.
    if(m_x < 0) SetPosition(0, m_y);
    if(m_y < 0) SetPosition(m_x, 0);
    if(m_x + m_width > g_winwidth) SetPosition(g_winwidth - m_width, m_y);
    if(m_y + m_height > g_winheight) SetPosition(m_x, g_winheight - m_height);

    return false;
}

void Window::Update() {
    m_widgetmanager->Update();
}

void Window::PostUpdate() {
    //printf("post update\n");
    if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x + m_width
    && g_mouse->m_y >= m_y && g_mouse->m_y < m_y + m_height) {
        g_mouse->m_havebeenused = true;
    }
}

void Window::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);

    m_widgetmanager->Draw();

    DrawRectangle(m_x, m_y, m_width, 12, m_titlebarcolor);

    DrawRectangle(m_x + m_width - 12, m_y, 12, 12, RED);
    DrawRectangleLines(m_x + m_width - 12, m_y, 12, 12, WHITE);

    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);
    DrawText(m_titlebartext.c_str(), m_x + 2, m_y + 2, 10, m_titlebartextcolor);
}

void Window::SetPosition(int x, int y) {
    m_x = x;
    m_y = y;

    m_widgetmanager->UpdateAllPos();
}