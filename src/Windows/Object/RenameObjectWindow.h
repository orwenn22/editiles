#ifndef RENAME_OBJECT_WINDOW_H
#define RENAME_OBJECT_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class ObjectTemplate;

class RenameObjectWindow : public Window {
    public:
    RenameObjectWindow(ObjectTemplate* objptr);

    ObjectTemplate* m_objptr;
    std::string m_newname;
};

#endif