#include "TexturePreview.h"

#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Themes/ColorTheme.h"
#include "../TextureManager/TextureObject.h"

#include <raylib.h>

TexturePreview::TexturePreview(int x, int y, int w, int h, TextureObject* textureobject) : Widget(x, y, w, h) {
    m_textureobj = textureobject;

    m_followmouse = false;
    m_mouseoffsetx = 0;
    m_mouseoffsety = 0;

    m_texturex = 0;
    m_texturey = 0;
}

void TexturePreview::Update() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                m_followmouse = true;
                m_mouseoffsetx = m_texturex - g_mouse->m_x;
                m_mouseoffsety = m_texturey - g_mouse->m_y;
            }
        }
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_followmouse = false;
    }

    if(m_followmouse) {
        m_texturex = g_mouse->m_x + m_mouseoffsetx;
        m_texturey = g_mouse->m_y + m_mouseoffsety;
    }
}

void TexturePreview::Draw() {
    DrawRectangleLines(m_x, m_y, m_width, m_height, g_colortheme.OutlineColor);
    DrawTextureRec(
        m_textureobj->m_texture,
        {(float)-m_texturex, (float)-m_texturey, (float)(m_width-2), (float)(m_height-2)},
        {(float)(m_x+1), (float)(m_y+1)},
        WHITE
    );
}