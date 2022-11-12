#include "Widget.h"

#include "WidgetManager.h"
#include "../Window.h"

#include <raylib.h>
#include <stdio.h>

Widget::Widget(int x, int y, int w, int h) {
    m_xoffset = x;
    m_yoffset = y;

    m_width = w;
    m_height = h;
}

Widget::~Widget() {
    printf("Destroyed Widget\n");
}

void Widget::Update() {
    
}

void Widget::UpdatePos() {
    m_x = m_parrent->m_baseposx + m_xoffset;
    m_y = m_parrent->m_baseposy + m_yoffset;
}

void Widget::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, RED);
}

void Widget::SetPos(int x, int y) {
    m_xoffset = x;
    m_yoffset = y;

    UpdatePos();
}