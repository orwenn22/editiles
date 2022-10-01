#ifndef GRID_LAYER_H
#define GRID_LAYER_H

#include "Layer.h"

#include <string>

class GridLayer : public Layer {
    public:
    GridLayer(short gridwidth, short gridheight, Level* level);
    virtual ~GridLayer();

    void Update() override;
    void Draw(int x, int y) override;

    void DrawNumbers(int x, int y);

    void SetBoxValue(unsigned int xpos, unsigned int yps, unsigned short value);

    //private:
    unsigned short* m_griddata;

    std::string m_tilemapname;      //timemap name saved into file
};

#endif