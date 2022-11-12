#include "CppStringValue.h"

#include <raylib.h>

CppStringValue::CppStringValue(int x, int y, std::string* stringptr) : Widget(x, y, 0, 0) {
    m_stringptr = stringptr;
}

void CppStringValue::Draw() {
    DrawText(m_stringptr->c_str(), m_x, m_y, 10, WHITE);
}