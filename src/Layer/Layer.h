#ifndef LAYER_H
#define LAYER_H

#include <string>

class Level;
class TextureObject;

class Layer {
    public:
    Layer(short gridwidth, short gridheight, Level* level);
    virtual ~Layer();

    virtual void Update();
    virtual void Draw(int x, int y);
    virtual void DrawNumbers(int x, int y);

    void SetBoxSize(unsigned short width, unsigned short height);

    //private:

    //type of layer
    int m_type;

    //size of the grid in box count
    unsigned short m_width;
    unsigned short m_height;

    //size of a single box in pixel
    unsigned short m_boxwidth;
    unsigned short m_boxheight;

    Level* m_parrent;

    std::string m_name;

    bool m_havetexture;
    TextureObject* m_textureobj;

};

#endif