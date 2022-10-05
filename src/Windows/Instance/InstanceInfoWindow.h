#ifndef INSTANCE_INFO_WINDOW_H
#define INSTANCE_INFO_WINDOW_H

#include "../../GUI/Window.h"

class Instance;

class InstanceInfoWindow : public Window {
    public:
    InstanceInfoWindow(WindowManager* winmanager, Instance* instranceptr);

    Instance* m_instanceptr;
};

#endif