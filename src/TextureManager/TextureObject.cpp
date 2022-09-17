#include "TextureObject.h"

#include "../Editor.h"
#include "../Level.h"

#include <raylib.h>
//#include <stdio.h>

extern Editor* g_editor;

TextureObject::TextureObject(std::string filepath, std::string name) {
    m_texture = LoadTexture(filepath.c_str());

    m_tilewidth = g_editor->m_level->m_boxwidth;
    m_tileheight = g_editor->m_level->m_boxheight;

    m_tilecountx = m_texture.width / m_tilewidth;
    m_tilecounty = m_texture.height / m_tileheight;

    m_tilecount = m_tilecountx * m_tilecounty;

    m_name = name;

    //printf("tile count : X : %i  | Y %i  | TOTAL %i\n", m_tilecountx, m_tilecounty, m_tilecount);
}

TextureObject::~TextureObject() {
    UnloadTexture(m_texture);
}

void TextureObject::DrawTile(int x, int y, unsigned short tileid, int scale) {
    if(tileid < m_tilecount && scale > 0) {
        int xontexture = (tileid % m_tilecountx) * m_tilewidth;
        int yontexture = (tileid / m_tilecountx) * m_tileheight;
        //DrawTextureRec(m_texture, {(float)xontexture, (float)yontexture, (float)m_tilewidth, (float)m_tileheight}, {(float)x, (float)y}, WHITE);
        DrawTexturePro(
            m_texture,
            {(float)xontexture, (float)yontexture, (float)m_tilewidth, (float)m_tileheight},
            {(float)x, (float)y, (float)(m_tilewidth*scale), (float)(m_tileheight*scale)},
            {0, 0},
            0,
            WHITE
        );
    }
}