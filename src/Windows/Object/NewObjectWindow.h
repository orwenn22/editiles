#ifndef NEW_OBJECT_WINDOW_H
#define NEW_OBJECT_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class NewObjectWindow : public Window {
    public:
    NewObjectWindow(WindowManager* winmanager);

    std::string m_newobjname;
};

#endif