#ifndef OBJECT_INFO_WINDOW_H
#define OBJECT_INFO_WINDOW_H

#include "../../GUI/Window.h"

class Editor;
class Level;
class ObjectTemplate;

class ObjectInfoWindow : public Window {
    public:
    ObjectInfoWindow(ObjectTemplate* objptr, Editor* editor);


    ObjectTemplate* m_objptr;
    Level* m_level;             //The level containing the object, aquiered from editor in the constructor.
};

#endif