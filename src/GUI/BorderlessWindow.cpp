#include "BorderlessWindow.h"

#include "MainWindow.h"
#include "Mouse/MouseObject.h"
#include "Widget/WidgetManager.h"
#include "WindowManager.h"

BorderlessWindow::BorderlessWindow() : Window() {

}

BorderlessWindow::~BorderlessWindow() {
    
}

bool BorderlessWindow::PreUpdate() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x + m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y + m_height) {  //on window
            m_parrent->BringOnTop(this);
            m_followmouse = true;
            m_xmouseoffset = m_x - g_mouse->m_x;
            m_ymouseoffset = m_y - g_mouse->m_y;
        }
    }


    if(m_followmouse) {
        SetPosition(g_mouse->m_x + m_xmouseoffset, g_mouse->m_y + m_ymouseoffset);
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

void BorderlessWindow::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);

    m_widgetmanager->Draw();

    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);
}