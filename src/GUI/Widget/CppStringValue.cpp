#include "CppStringValue.h"

#include <raylib.h>

CppStringValue::CppStringValue(WidgetManager* widgetmanager, int x, int y, std::string* stringptr) : Widget(widgetmanager, x, y, 0, 0) {
    m_stringptr = stringptr;
}

void CppStringValue::Draw() {
    DrawText(m_stringptr->c_str(), m_x, m_y, 10, WHITE);
}