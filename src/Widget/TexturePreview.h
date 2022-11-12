#ifndef TEXTURE_PREVIEW_H
#define TEXTURE_PREVIEW_H

#include "../GUI/Widget/Widget.h"

class TextureObject;

class TexturePreview : public Widget {
    public:
    TexturePreview(int x, int y, int w, int h, TextureObject* textureobject);

    void Update() override;
    void Draw() override;

    TextureObject* m_textureobj;

    bool m_followmouse;
    int m_mouseoffsetx;
    int m_mouseoffsety;

    int m_texturex;
    int m_texturey;
};

#endif