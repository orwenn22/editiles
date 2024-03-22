#ifndef INSTANCE_LAYER_H
#define INSTANCE_LAYER_H

#include "Layer.h"

#include <string>
#include <vector>

class Instance;
class ObjectTemplate;

struct ObjectProperty;

class InstanceLayer : public Layer {
    public:
    InstanceLayer(std::string name);
    virtual ~InstanceLayer();

    void Update(int x, int y) override;
    void CheckMouseInput();

    void Draw(int x, int y) override;

    void Save(FILE* fileptr) override;

    void Add(Instance* newinstance);
    Instance* Get(int index);

    // Instances deleted with "NoTrashcan" functions are deallocated during the call.
    // With the other function, the destruction of the instance is delayed by one frame (to prevent invalid memory read from windows)
    // NOTE : in the destructor of instance, we remove the instance from its template.
    void RemoveWithIndex(int index);
    void RemoveWithIndexNoTrashcan(int index);
    void RemoveWithPtr(Instance* instanceptr);
    void RemoveWithPtrNoTrashcan(Instance* instanceptr);

    void Expand(int top, int left, int right, int bottom);

    int GetInstanceCount();

    void EmptyTrashcan();

    std::vector<Instance*> m_instances;
    int m_instancecount;        //This only exists because it is displayed in the layer's info
    std::vector<Instance*> m_trashcan;
};

#endif