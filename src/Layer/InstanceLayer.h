#ifndef INSTANCE_LAYER_H
#define INSTANCE_LAYER_H

#include "Layer.h"

#include <string>
#include <vector>

class Instance;
class ObjectTemplate;
class ObjectProperty;

class InstanceLayer : public Layer {
    public:
    InstanceLayer(Level* level, std::string name);
    virtual ~InstanceLayer();

    void Update(int x, int y) override;
    void CheckMouseInput();

    void Draw(int x, int y) override;

    void Save(FILE* fileptr) override;

    void Add(Instance* newinstance);
    Instance* Get(int index);
    void RemoveWithIndex(int index);
    void RemoveWithPtr(Instance* instanceptr);

    void AddPropertyToAllInstances(ObjectTemplate* instancestype, ObjectProperty* newproperty);
    void ChangePropertyToAllInstances(ObjectTemplate* instancestype, int propertyindex, int oldpropertytype, int oldpropertyvalue, int newpropertyvalue);
    void ChangePropertyToAllInstances(ObjectTemplate* instancestype, int propertyindex, int oldpropertytype, std::string oldpropertyvalue, std::string newpropertyvalue);
    void RemovePropertyFromInstances(ObjectTemplate* instancestype, int indextoremove);

    std::vector<Instance*> m_instances;
    int m_instancecount;
};

#endif