#include "Label.h"

#include "WidgetManager.h"

#include <raylib.h>

Label::Label(int x, int y, std::string text) : Widget(x, y, 0, 0) {
    m_text = text;
    m_color = {255, 255, 255, 255};
}

void Label::Draw() {
    DrawText(m_text.c_str(), m_x, m_y, 10, m_color);
}

void Label::SetText(std::string newtext) {
    m_text = newtext;
}

void Label::SetColor(Color newcolor) {
    m_color = newcolor;
}