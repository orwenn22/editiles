#ifndef PALETTE_H
#define PALETTE_H

#include "../GUI/Widget/Widget.h"

class Editor;
class Layer;

class Palette : public Widget {
    public:
    Palette(int x, int y, int w, int h, Editor* editor);

    void Update() override;
    void Draw() override;

    void DrawTiles(Layer* layer);   //show the tiles from the texutre of a layer

    int m_firstelement;     //the index of the fist tile visible at the top left of the palette
    int m_zoom;             //zoom factor of the palette

    Editor* m_editor;
};

#endif