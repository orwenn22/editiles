#include "Layer.h"

#include "LayerIDs.h"

Layer::Layer(Level* level) {
    m_type = LAYERID_STANDARD;

    m_parrent = level;

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