#ifndef OBJECT_PROPERTIES_LIST_H
#define OBJECT_PROPERTIES_LIST_H

#include "../GUI/Widget/ElementList.h"

class Editor;
class ObjectTemplate;

//This widget is used in ObjectInfoWindow
class ObjectPropertiesList : public ElementList {
    public:
    ObjectPropertiesList(int x, int y, int w, int h, ObjectTemplate* objptr, Editor* editor);

    int GetElementCount() override;
    void DrawElement(int painterx, int paintery, int elementindex) override;

    void RightClickOn(int elementindex) override;

    ObjectTemplate* m_objptr;

    Editor* m_editor;       //Editor is requiered to open more windows.
};

#endif