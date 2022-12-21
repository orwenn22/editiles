#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#include <raylib.h>
#include <string>

//TODO : support animated textures in the editor ?
class TextureObject {
    public:
    TextureObject(std::string filepath, std::string name, int tilewidth, int tileheight);
    ~TextureObject();

    void DrawTile(int x, int y, unsigned short tileid, int scale);
    void DrawTile(int x, int y, int drawwidth, int drawheight, unsigned short tileid);

    Texture m_texture;

    int m_tilecountx;
    int m_tilecounty;
    int m_tilewidth;
    int m_tileheight;

    int m_tilecount;

    std::string m_name;
};

#endif