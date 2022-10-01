#ifndef LAYER_H
#define LAYER_H

#include <string>

class Level;
class TextureObject;

class Layer {
    public:
    Layer(Level* level);
    virtual ~Layer();

    virtual void Update();
    virtual void Draw(int x, int y);
    virtual void DrawNumbers(int x, int y);

    //private:

    //type of layer
    int m_type;

    Level* m_parrent;

    std::string m_name;

    bool m_havetexture;
    TextureObject* m_textureobj;

};

#endif