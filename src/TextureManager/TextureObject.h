#ifndef TEXTURE_OBJECT_H
#define TEXUTRE_OBJECT_H

#include <raylib.h>
#include <string>

class TextureObject {
    public:
    TextureObject(std::string filepath, std::string name);
    ~TextureObject();

    void DrawTile(int x, int y, unsigned short tileid, int scale);

    Texture m_texture;

    int m_tilecountx;
    int m_tilecounty;
    int m_tilewidth;
    int m_tileheight;

    int m_tilecount;

    std::string m_name;
};

#endif