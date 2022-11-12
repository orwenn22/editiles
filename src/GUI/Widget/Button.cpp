#include "Button.h"

#include "../../Editor.h"
#include "../Mouse/MouseObject.h"

#include <raylib.h>
#include <stdio.h>

extern Editor* g_editor;

void DefaultButtonAction(Button* but) {
    printf("Defaut button action\n");
}

Button::Button(int x, int y, int w, int h) : Widget(x, y, w, h) {
    m_action = DefaultButtonAction;
    m_text = "";
}

void Button::Update() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x + m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y + m_height) {
            m_action(this);
            g_mouse->m_havebeenused = true;
        }
    }
}

void Button::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);
    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);
    DrawText(m_text.c_str(), m_x + 2, m_y + 2, 10, WHITE);
}

void Button::SetAction(ButtonAction action) {
    m_action = action;
}

void Button::SetText(std::string text) {
    m_text = text;
}