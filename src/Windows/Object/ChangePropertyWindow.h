#ifndef CHANGE_PROPERTY_WINDOW_H
#define CHANGE_PROPERTY_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class ObjectTemplate;
struct ObjectProperty;

class ChangePropertyWindow : public Window {
    public:
    ChangePropertyWindow(ObjectProperty* propptr, ObjectTemplate* objptr);


    int m_intval;
    std::string m_strval;

    ObjectProperty* m_propptr;
    ObjectTemplate* m_objptr;
};

#endif