#include "InstanceLayer.h"

#include "../FileUtil/FileUtil.h"
#include "../Level.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "Instance.h"
#include "LayerIDs.h"

InstanceLayer::InstanceLayer(std::string name) : Layer(name) {
    m_type = LAYERID_INSTANCE;
    m_instancecount = 0;
}

InstanceLayer::~InstanceLayer() {
    for(int i = 0; i < m_instancecount; i++) {
        delete m_instances[i];
    }
    m_instances.clear();
    m_instancecount = 0;
}

void InstanceLayer::Add(Instance* newinstance) {
    m_instances.push_back(newinstance);
    m_instancecount++;

    newinstance->m_parrent = this;
    newinstance->m_isinlayer = true;
}

Instance* InstanceLayer::Get(int index) {
    if(index >= 0 && index < m_instancecount) {
        return m_instances[index];
    }
    return NULL;
}

void InstanceLayer::Save(FILE* fileptr) {
    Layer::Save(fileptr);

    //number of instance
    WriteInt(fileptr, m_instancecount);

    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Save(fileptr);
    }
}

void InstanceLayer::RemoveWithIndex(int index) {
    if(index >= 0 && index < m_instancecount) {
        delete m_instances[index];
        m_instances.erase(m_instances.begin() + index);
        m_instancecount--;
    }
}

void InstanceLayer::RemoveWithPtr(Instance* instanceptr) {
    for(int i = 0; i < m_instancecount; i++) {
        if(m_instances[i] == instanceptr) {
            RemoveWithIndex(i);
            return;
        }
    }
}

void InstanceLayer::Update(int x, int y) {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Update(x, y, m_parrent->m_zoom);
    }
}

void InstanceLayer::CheckMouseInput() {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->CheckMouseInput();
    }
}

void InstanceLayer::Draw(int x, int y) {
    for(int i = 0; i < m_instancecount; i++) {
        m_instances[i]->Draw();
    }
}


void InstanceLayer::Expand(int top, int left, int right, int bottom) {
    for(Instance* i : m_instances) {
        i->m_properties[i->GetPropertyIndex("x")].as_int += left*m_parrent->m_boxwidth;
        i->m_properties[i->GetPropertyIndex("y")].as_int += top*m_parrent->m_boxheight;
    }
}