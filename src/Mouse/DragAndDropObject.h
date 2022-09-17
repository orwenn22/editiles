#ifndef DRAG_AND_DROP_OBJECT_H
#define DRAG_AND_DROP_OBJECT_H

#include <string>

union DragAndDropData {
    int as_int;
    void* as_ptr;
};

struct DragAndDropObject {
    DragAndDropObject();
    
    DragAndDropObject(int type, int intvalue);
    DragAndDropObject(int type, void* ptrvalue);

    DragAndDropObject(int type, int intvalue, std::string text);
    DragAndDropObject(int type, void* ptrvalue, std::string text);

    int m_type;
    DragAndDropData m_data;
    std::string m_text;
};

#endif