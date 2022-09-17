#ifndef LAYER_LIST_H
#define LAYER_LIST_H

#include "../GUI/Widget/Widget.h"

class LayerList : public Widget {
    public:
    LayerList(WidgetManager* widgetmanager, int x, int y, int w, int h);

    void Update() override;
    void Draw() override;

    int m_firstelementindex;
};

#endif