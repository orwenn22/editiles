#ifndef LAYER_LIST_WINDOW_H
#define LAYER_LIST_WINDOW_H

#include "../../GUI/Window.h"

class Level;

class LayerListWindow : public Window {
    public:
    LayerListWindow(Level* level);

    Level* m_level;
};

#endif