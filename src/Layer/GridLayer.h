#ifndef GRID_LAYER_H
#define GRID_LAYER_H

#include "Layer.h"

#include <string>

class GridLayer : public Layer {
    public:
    GridLayer(short gridwidth, short gridheight, Level* level, std::string name);
    virtual ~GridLayer();

    void Draw(int x, int y) override;

    void DrawNumbers(int x, int y) override;

    void SetBoxSize(unsigned short width, unsigned short height);
    void SetBoxValue(unsigned int xpos, unsigned int yps, unsigned short value);

    void Save(FILE* fileptr) override;

    //private:
    unsigned short* m_griddata;

    std::string m_tilemapname;      //timemap name saved into file

    //size of the grid in box count
    unsigned short m_width;
    unsigned short m_height;

    //size of a single box in pixel
    unsigned short m_boxwidth;
    unsigned short m_boxheight;
};

#endif