#ifndef LAYER_INFO_WINDOW_H
#define LAYER_INFO_WINDOW_H

#include "../GUI/Window.h"

class Layer;

class LayerInfoWindow : public Window {
    public:
    LayerInfoWindow(WindowManager* winmanager, Layer* layerptr);

    Layer* m_layerpointer;
};

#endif