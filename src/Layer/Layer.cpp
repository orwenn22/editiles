#include "Layer.h"

#include "../FileUtil/FileUtil.h"
#include "LayerIDs.h"

Layer::Layer(std::string name) {
    m_type = LAYERID_STANDARD;

    m_isinlevel = false;

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

void Layer::Save(FILE* fileptr) {
    //printf("TODO : implement saving for specific layer\n");
    
    //layer type
    WriteShort(fileptr, (short)m_type);

    //layer name
    fputs(m_name.c_str(), fileptr);
    putc(0, fileptr);
}