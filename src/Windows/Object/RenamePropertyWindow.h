#ifndef RENAME_PROPERTY_WINDOW_H
#define RENAME_PROPERTY_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class ObjectTemplate;
struct ObjectProperty;

class RenamePropertyWindow : public Window {
    public:
    RenamePropertyWindow(WindowManager* winmanager, ObjectTemplate* objptr, ObjectProperty* propptr);

    std::string m_newname;

    ObjectTemplate* m_objptr;
    ObjectProperty* m_propptr;
};

#endif