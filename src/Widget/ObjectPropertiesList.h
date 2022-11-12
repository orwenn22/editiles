#ifndef OBJECT_PROPERTIES_LIST_H
#define OBJECT_PROPERTIES_LIST_H

#include "../GUI/Widget/ElementList.h"

class ObjectTemplate;

class ObjectPropertiesList : public ElementList {
    public:
    ObjectPropertiesList(int x, int y, int w, int h, ObjectTemplate* objptr);

    int GetElementCount() override;
    void DrawElement(int painterx, int paintery, int elementindex) override;

    void RightClickOn(int elementindex) override;

    ObjectTemplate* m_objptr;
};

#endif