#ifndef LAYER_H
#define LAYER_H

#include <string>

class Level;
class TextureObject;

class Layer {
    public:
    Layer(std::string name);
    virtual ~Layer();

    virtual void Update(int x, int y);
    virtual void Draw(int x, int y);
    virtual void DrawNumbers(int x, int y);

    virtual void Save(FILE* fileptr);

    //private:

    //type of layer
    int m_type;

    Level* m_parrent;
    bool m_isinlevel;

    std::string m_name;

    bool m_havetexture;
    TextureObject* m_textureobj;

};

#endif