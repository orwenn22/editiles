#ifndef INSTANCE_LAYER_H
#define INSTANCE_LAYER_H

#include "Layer.h"

#include <vector>

class Instance;

class InstanceLayer : public Layer {
    public:
    InstanceLayer(Level* level, std::string name);
    virtual ~InstanceLayer();

    void Update(int x, int y) override;
    void Draw(int x, int y) override;

    void Add(Instance* newinstance);
    Instance* Get(int index);
    void RemoveWithIndex(int index);
    void RemoveWithPtr(Instance* instanceptr);
    void CheckMouseInput();

    std::vector<Instance*> m_instances;
    int m_instancecount;
};

#endif