#include "IntValue.h"

#include <raylib.h>

IntValue::IntValue(int x, int y, int* value) : Widget(x, y, 0, 0) {
    m_value = value;
}

void IntValue::Draw() {
    DrawText(TextFormat("%i", *m_value), m_x, m_y, 10, WHITE);
}