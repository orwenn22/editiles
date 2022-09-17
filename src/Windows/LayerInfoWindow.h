#ifndef LAYER_INFO_WINDOW_H
#define LAYER_INFO_WINDOW_H

#include "../GUI/Window.h"

class GridLayer;

class LayerInfoWindow : public Window {
    public:
    LayerInfoWindow(WindowManager* winmanager, GridLayer* layerptr);

    GridLayer* m_layerpointer;
};

#endif