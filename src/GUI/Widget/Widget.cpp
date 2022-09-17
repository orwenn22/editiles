#include "Widget.h"

#include "WidgetManager.h"
#include "../Window.h"

#include <raylib.h>
#include <stdio.h>

Widget::Widget(WidgetManager* wm, int x, int y, int w, int h) {
    m_parrent = wm;

    m_xoffset = x;
    m_yoffset = y;

    m_width = w;
    m_height = h;

    UpdatePos();
}

Widget::~Widget() {
    printf("Destroyed Widget\n");
}

void Widget::Update() {
    
}

void Widget::UpdatePos() {
    m_x = m_parrent->m_window->m_x + m_xoffset;
    m_y = m_parrent->m_window->m_y + m_yoffset;
}

void Widget::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, RED);
}

void Widget::SetPos(int x, int y) {
    m_xoffset = x;
    m_yoffset = y;

    UpdatePos();
}