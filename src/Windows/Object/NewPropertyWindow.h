#ifndef NEW_PROPERTY_WINDOW_H
#define NEW_PROPERTY_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class ObjectTemplate;

class NewPropertyWindow : public Window {
    public:
    NewPropertyWindow(ObjectTemplate* objptr);
    

    ObjectTemplate* m_objptr;
    std::string m_newpropertyname;
};

#endif