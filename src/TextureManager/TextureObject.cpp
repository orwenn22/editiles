#include "TextureObject.h"

#include <raylib.h>
//#include <stdio.h>

//FIXME: currently the tilewidth and tileheight parameters are passed in ImageFileReceiver and TextureList.
//       Maybe instead of that it cound be a good idea to open a dialog box and make the user type the tile sizes.
TextureObject::TextureObject(std::string filepath, std::string name, int tilewidth, int tileheight) {
    m_texture = LoadTexture(filepath.c_str());

    m_tilewidth = tilewidth;
    m_tileheight = tileheight;

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

void TextureObject::DrawTile(int x, int y, int drawwidth, int drawheight, unsigned short tileid) {
    if(tileid < m_tilecount) {
        int xontexture = (tileid % m_tilecountx) * m_tilewidth;
        int yontexture = (tileid / m_tilecountx) * m_tileheight;
        DrawTexturePro(
            m_texture,
            {(float)xontexture, (float)yontexture, (float)m_tilewidth, (float)m_tileheight},
            {(float)x, (float)y, (float)(drawwidth), (float)(drawheight)},
            {0, 0},
            0,
            WHITE
        );
    }
}
