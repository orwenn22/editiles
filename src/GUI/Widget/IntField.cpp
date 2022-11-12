#include "IntField.h"

#include "../Mouse/MouseObject.h"
#include "../Window.h"
#include "WidgetManager.h"

#include <raylib.h>

IntField::IntField(int x, int y, int w, int* variableptr) : Widget(x, y, w, 16) {
    m_varriableptr = variableptr;
    m_tempvariable = *m_varriableptr;

    m_isselected = false;

    m_allownegative = true;
    m_allownull = true;

    m_minvalue = -10000;
    m_maxvalue =  10000;
}

void IntField::Update() {
    if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {    //deselect/confirm
        bool wasselected = m_isselected;
        m_isselected = false;

        /*if(m_allownull == false && (*m_varriableptr) == 0) {
            (*m_varriableptr) = 1;
        }*/

        if(m_tempvariable == 0 && m_allownull == false) {
            m_tempvariable = 1;
        }
        
        if(m_tempvariable < m_minvalue) m_tempvariable = m_minvalue;
        if(m_tempvariable > m_maxvalue) m_tempvariable = m_maxvalue;

        if(wasselected) {
            (*m_varriableptr) = m_tempvariable;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {       //select
            if(g_mouse->m_havebeenused == false) {
                if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x + m_width
                && g_mouse->m_y >= m_y && g_mouse->m_y < m_y + m_height) {
                    m_isselected = true;
                    g_mouse->m_havebeenused = true;
                    m_tempvariable = (*m_varriableptr);
                }
            }
        }
    }

    if(m_isselected) {
        if(IsKeyPressed(KEY_UP)) {
            m_tempvariable+=1;
        }
        if(IsKeyPressed(KEY_DOWN)) {
            m_tempvariable-=1;
        }

        if(IsKeyPressed(KEY_BACKSPACE)) {
            m_tempvariable /= 10;
        }

        if(IsKeyPressed(KEY_KP_SUBTRACT) && m_allownegative) {
            m_tempvariable = - m_tempvariable;
        }

        for(int i = KEY_KP_0; i < KEY_KP_9+1; i++) {
            if(IsKeyPressed(i)) {
                m_tempvariable = m_tempvariable * 10 + (i-320);
            }
        }

        //m_parrent->UpdateAllPos();
    }
}

void IntField::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);
    //DrawText(TextFormat("%i", m_tempvariable), m_x + 2, m_y + 2, 10, WHITE);
    if(m_isselected) {
        DrawRectangleLines(m_x, m_y, m_width, m_height, YELLOW);
        DrawText(TextFormat("%i", m_tempvariable), m_x + 2, m_y + 2, 10, WHITE);
    } else {
        DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);
        DrawText(TextFormat("%i", *m_varriableptr), m_x + 2, m_y + 2, 10, WHITE);
    }
}

void IntField::SetTargetVariable(int* variableptr) {
    m_varriableptr = variableptr;
}


void IntField::AllowNegative(bool allow) {
    m_allownegative = allow;
}

void IntField::AllowNull(bool allow) {
    m_allownull = allow;
}

void IntField::SetMinMax(int min, int max) {
    if(min < max) {
        m_minvalue = min;
        m_maxvalue = max;
    }
}