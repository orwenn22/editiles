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

    int m_type;                 //type of data in the d&d object. User-definded.
    DragAndDropData m_data;     //data stored in the d&d object. Can be an int or a pointer to something.
    std::string m_text;         //text that will be displayed when MouseObject::Draw() is called.
};

#endif