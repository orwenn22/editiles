#include "Instance.h"

#include "../DragObjectIDs.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"

#include <raylib.h>

extern int g_winwidth;
extern int g_winheight;

extern MouseObject* g_mouse;

Instance::Instance(ObjectTemplate* objtemplate, int x, int y) {
    m_objtemplateptr = objtemplate;

    for(int i = 0; i < m_objtemplateptr->m_propertycount; i++) {
        ObjectProperty* objectprop = m_objtemplateptr->GetProperty(i);

        InstancePropertyValue instanceprop;

        if(objectprop->name == "x") {
            instanceprop.as_int = x;
            m_properties.push_back(instanceprop);
        }
        else if(objectprop->name == "y") {
            instanceprop.as_int = y;
            m_properties.push_back(instanceprop);
        } else {
            if(objectprop->type == OPT_INT) {
                instanceprop.as_int = objectprop->defaultvalue.as_int;
            } else if(objectprop->type == OPT_STR) {
                for(int j = 0; j < 255; j++) {
                    char c = objectprop->defaultvalue.as_str[j];
                    instanceprop.as_str[j] = c;
                    if(c == 0) break;
                }
            }
            m_properties.push_back(instanceprop);
        }
    }
}

void Instance::Update(int levelx, int levely, int zoom) {
    m_x = levelx + (m_properties[m_objtemplateptr->GetPropertyIndex("x")].as_int * zoom);
    m_y = levely + (m_properties[m_objtemplateptr->GetPropertyIndex("y")].as_int * zoom);

    m_width = m_properties[m_objtemplateptr->GetPropertyIndex("width")].as_int * zoom;
    m_height = m_properties[m_objtemplateptr->GetPropertyIndex("height")].as_int * zoom;

    m_drawonscreen = !(m_x+m_width < 0 || m_y+m_height < 0 || m_x > g_winwidth || m_y > g_winheight);
}

void Instance::CheckMouseInput() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    printf("WOW\n");
                    printf("property count : %li\n", m_properties.size());

                    g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_INSTANCE, this, "Instance"));
            }
            g_mouse->m_havebeenused = false;
        }
    }
}

void Instance::Draw() {
    if(m_drawonscreen) {
        DrawRectangle(m_x, m_y, m_width, m_height, RED);
    }
}


void Instance::MoveTo(int x, int y) {
    m_properties[m_objtemplateptr->GetPropertyIndex("x")].as_int = x;
    m_properties[m_objtemplateptr->GetPropertyIndex("y")].as_int = y;
}