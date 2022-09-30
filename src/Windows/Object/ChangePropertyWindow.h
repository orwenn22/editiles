#ifndef CHANGE_PROPERTY_WINDOW_H
#define CHANGE_PROPERTY_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

struct ObjectProperty;

class ChangePropertyWindow : public Window {
    public:
    ChangePropertyWindow(WindowManager* winmanager, ObjectProperty* propptr);


    int m_intval;
    std::string m_strval;

    ObjectProperty* m_propptr;
};

#endif