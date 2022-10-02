#include "Layer.h"

#include "LayerIDs.h"

Layer::Layer(Level* level, std::string name) {
    m_type = LAYERID_STANDARD;

    m_parrent = level;

    m_name = name;

    m_havetexture = false;
}

Layer::~Layer() {

}

void Layer::Update(int x, int y) {

}

void Layer::Draw(int x, int y) {

}

void Layer::DrawNumbers(int x, int y) {
    
}