#ifndef TEXTURE_LIST_H
#define TEXTURE_LIST_H

#include "../GUI/Widget/Widget.h"

class WidgetManager;

class TextureList : public Widget {
    public:
    TextureList(WidgetManager* wm, int x, int y, int w, int h);

    void Update() override;
    void Draw() override;

    int m_firstelementindex;

    //for double clicking
    /*bool m_issomethingclicked;
    int m_clickedelement;
    int m_timesinceclick;*/
};

#endif