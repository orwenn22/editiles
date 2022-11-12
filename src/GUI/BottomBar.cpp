#include "BottomBar.h"

#include "MainWindow.h"
#include "Mouse/MouseObject.h"

BottomBar::BottomBar() {
    m_text = "";
}

void BottomBar::Update() {
    TextClear();
    m_y = g_winheight-15;

    if(g_mouse->m_y >= m_y) {
        g_mouse->m_havebeenused = true;
    }
}

void BottomBar::Draw() {
    DrawRectangle(0, m_y, g_winwidth, 15, BLACK);
    DrawLine(0, m_y, g_winwidth, m_y, WHITE);

    DrawText(m_text.c_str(), 3, m_y+3, 10, WHITE);
}

void BottomBar::TextAppend(std::string strtoappend) {
    m_text += strtoappend;
}

void BottomBar::TextClear() {
    m_text = "";
}