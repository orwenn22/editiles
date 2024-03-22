#include "InstanceLayer.h"

#include "../FileUtil/FileUtil.h"
#include "../Level.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "Instance.h"
#include "LayerIDs.h"

InstanceLayer::InstanceLayer(std::string name) : Layer(name) {
    m_type = LAYERID_INSTANCE;
    m_instancecount = 0;    //This only exists because it is displayed in the layer's info
}

InstanceLayer::~InstanceLayer() {
    for(Instance *i : m_instances) delete i;
    m_instances.clear();
    EmptyTrashcan();
    m_instancecount = 0;
}

void InstanceLayer::Add(Instance* newinstance) {
    m_instances.push_back(newinstance);

    newinstance->m_parrent = this;
    newinstance->m_isinlayer = true;
}

Instance* InstanceLayer::Get(int index) {
    if(index >= 0 && index < (int)(m_instances.size())) {
        return m_instances[index];
    }
    return nullptr;
}

void InstanceLayer::Save(FILE* fileptr) {
    Layer::Save(fileptr);

    //number of instance
    WriteInt(fileptr, (int)(m_instances.size()));

    for(int i = 0; i < (int)(m_instances.size()); i++) {
        m_instances[i]->Save(fileptr);
    }
}

void InstanceLayer::RemoveWithIndex(int index) {
    if(index >= 0 && index < (int)(m_instances.size())) {
        m_trashcan.push_back(m_instances[index]);
        m_instances.erase(m_instances.begin() + index);
    }
}

void InstanceLayer::RemoveWithIndexNoTrashcan(int index) {
    if(index >= 0 && index < (int)(m_instances.size())) {
        delete m_instances[index];
        m_instances.erase(m_instances.begin() + index);
    }
}


void InstanceLayer::RemoveWithPtr(Instance* instanceptr) {
    for(int i = 0; i < (int)(m_instances.size()); i++) {
        if(m_instances[i] == instanceptr) {
            RemoveWithIndex(i);
            return;
        }
    }
}

//This is used bvy the destructor of ObjectTemplate to properly remove its children
void InstanceLayer::RemoveWithPtrNoTrashcan(Instance* instanceptr) {
    for(int i = 0; i < (int)(m_instances.size()); i++) {
        if(m_instances[i] == instanceptr) {
            RemoveWithIndexNoTrashcan(i);
            return;
        }
    }
}

void InstanceLayer::Update(int x, int y) {
    EmptyTrashcan();    //This will delay the destruction of objects by 1 frame

    for(int i = 0; i < (int)(m_instances.size()); i++) {
        m_instances[i]->Update(x, y, m_parrent->m_zoom);
    }
    m_instancecount = GetInstanceCount();
}

void InstanceLayer::CheckMouseInput() {
    for(int i = 0; i < (int)(m_instances.size()); i++) {
        m_instances[i]->CheckMouseInput();
    }
}

void InstanceLayer::Draw(int x, int y) {
    for(int i = 0; i < (int)(m_instances.size()); i++) {
        m_instances[i]->Draw();
    }
}


void InstanceLayer::Expand(int top, int left, int right, int bottom) {
    for(Instance* i : m_instances) {
        i->m_properties[i->GetPropertyIndex("x")].as_int += left*m_parrent->m_boxwidth;
        i->m_properties[i->GetPropertyIndex("y")].as_int += top*m_parrent->m_boxheight;
    }
}

int InstanceLayer::GetInstanceCount() {
    return (int)(m_instances.size());
}

void InstanceLayer::EmptyTrashcan() {
    for(Instance *i : m_trashcan) delete i;
    m_trashcan.clear();
}
