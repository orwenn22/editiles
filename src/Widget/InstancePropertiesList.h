#ifndef INSTANCE_PROPERTIES_LIST_H
#define INSTANCE_PROPERTIES_LIST_H

#include "../GUI/Widget/ElementList.h"

class Instance;

class InstancePropertiesList : public ElementList {
    public:
    InstancePropertiesList(Instance* instanceptr, int x, int y, int w, int h);

    int GetElementCount() override;
    void DrawElement(int painterx, int paintery, int elementindex) override;

    void RightClickOn(int elementindex) override;

    Instance* m_instanceptr;
};

#endif