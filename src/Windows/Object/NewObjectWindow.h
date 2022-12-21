#ifndef NEW_OBJECT_WINDOW_H
#define NEW_OBJECT_WINDOW_H

#include "../../GUI/Window.h"

#include <string>

class ObjectManager;

class NewObjectWindow : public Window {
    public:
    NewObjectWindow(ObjectManager* objectmanager);

    std::string m_newobjname;
    ObjectManager* m_objectmanager;
};

#endif