#ifndef OBJECT_INFO_WINDOW_H
#define OBJECT_INFO_WINDOW_H

#include "../../GUI/Window.h"

class ObjectTemplate;

class ObjectInfoWindow : public Window {
    public:
    ObjectInfoWindow(ObjectTemplate* objptr);


    ObjectTemplate* m_objptr;
};

#endif