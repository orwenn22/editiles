#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "../GUI/Widget/ElementList.h"

class ObjectList : public ElementList {
    public:
    ObjectList(WidgetManager* widgetmanager, int x, int y, int w, int h);

    void RightClickOn(int clickindex) override;

    void DrawElement(int painterx, int paintery, int elementindex);

    int GetElementCount() override;
};

#endif