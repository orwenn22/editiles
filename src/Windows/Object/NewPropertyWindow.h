#ifndef NEW_PROPERTY_WINDOW_H
#define NEW_PROPERTY_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

struct ObjectTemplate;

class NewPropertyWindow : public Window {
    public:
    NewPropertyWindow(WindowManager* winmanager, ObjectTemplate* objptr);
    

    ObjectTemplate* m_objptr;
    std::string m_newpropertyname;
};

#endif