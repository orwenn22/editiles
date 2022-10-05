#ifndef CHANGE_INSTANCE_PROP_WINDOW_H
#define CHANGE_INSTANCE_PROP_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class Instance;
struct ObjectProperty;

class ChangeInstancePropWindow : public Window {
    public:
    ChangeInstancePropWindow(WindowManager* winmanager, Instance* instanceptr, ObjectProperty* propertyptr);

    int m_proptype;     //property's variable type

    Instance* m_instanceptr;
    ObjectProperty* m_propertyptr;

    int m_intval;
    std::string m_strval;
};

#endif