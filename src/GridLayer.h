#ifndef GRID_LAYER_H
#define GRID_LAYER_H

#include <string>

class Level;
class TextureObject;

class GridLayer {
    public:
    GridLayer(short gridwidth, short gridheight, Level* level);
    ~GridLayer();

    void Update();
    void Draw(int x, int y);
    void DrawNumbers(int x, int y);

    void SetBoxValue(unsigned int xpos, unsigned int yps, unsigned short value);
    
    void SetBoxSize(unsigned short width, unsigned short height);
    //private:
    unsigned short m_width;
    unsigned short m_height;

    unsigned short m_boxwidth;
    unsigned short m_boxheight;

    unsigned short* m_griddata;

    Level* m_parrent;

    std::string m_name;

    bool m_havetexture;
    TextureObject* m_textureobj;
};

#endif