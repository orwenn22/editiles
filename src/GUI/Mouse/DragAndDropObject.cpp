#include "DragAndDropObject.h"

DragAndDropObject::DragAndDropObject() {
    m_type = -1;
    m_data.as_int = 0;
    m_text = "Unknown object :(";
}

DragAndDropObject::DragAndDropObject(int type, int intvalue) {
    m_type = type;
    m_data.as_int = intvalue;
    m_text = "No description";
}

DragAndDropObject::DragAndDropObject(int type, void* ptrvalue) {
    m_type = type;
    m_data.as_ptr = ptrvalue;
    m_text = "No description";
}

DragAndDropObject::DragAndDropObject(int type, int intvalue, std::string text) {
    m_type = type;
    m_data.as_int = intvalue;
    m_text = text;
}

DragAndDropObject::DragAndDropObject(int type, void* ptrvalue, std::string text) {
    m_type = type;
    m_data.as_ptr = ptrvalue;
    m_text = text;
}