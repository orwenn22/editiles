#include "Layer.h"

#include "LayerIDs.h"

Layer::Layer(short gridwidth, short gridheight, Level* level) {
    m_type = LAYERID_STANDARD;

    m_parrent = level;

    m_width = gridwidth;
    m_height = gridheight;
    m_boxwidth = 16;
    m_boxheight = 16;

    m_name = "Layer";

    m_havetexture = false;
}

Layer::~Layer() {

}

void Layer::Update() {

}

void Layer::Draw(int x, int y) {

}

void Layer::DrawNumbers(int x, int y) {
    
}

void Layer::SetBoxSize(unsigned short width, unsigned short height) {
    m_boxwidth = width;
    m_boxheight = height;
}