#include "InstanceLayer.h"

#include "../Level.h"
#include "Instance.h"
#include "LayerIDs.h"

InstanceLayer::InstanceLayer(Level* level, std::string name) : Layer(level, name) {
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
}

Instance* InstanceLayer::Get(int index) {
    if(index >= 0 && index < m_instancecount) {
        return m_instances[index];
    }
    return NULL;
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