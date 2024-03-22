#include "Instance.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../FileUtil/FileUtil.h"
#include "../GUI/MainWindow.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../ObjectManager/ObjectManager.h"
#include "../ObjectManager/ObjectProperty.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../TextureManager/TextureObject.h"
#include "../Windows/Instance/InstanceInfoWindow.h"
#include "../Windows/WinIDs.h"
#include "InstanceLayer.h"

#include <raylib.h>

//TODO: find a better way to access the level's parrent editor from here ?
//                  layer      level     editor
#define leveditor m_parrent->m_parrent->m_editor

Instance::Instance(ObjectTemplate* objtemplate, int x, int y) {
    m_objtemplateptr = objtemplate;
    m_objtemplateptr->AddChildren(this);
    m_isinlayer = false;
    m_drawonscreen = false;

    //Add all the properties to the instance with their default values from the ObjectTemplate
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

Instance::~Instance() {
    printf("Destroyed instance\n");
    m_objtemplateptr->RemoveChildren(this);
}

void Instance::Update(int levelx, int levely, int zoom) {
    m_x = levelx + (m_properties[GetPropertyIndex("x")].as_int * zoom);
    m_y = levely + (m_properties[GetPropertyIndex("y")].as_int * zoom);

    m_width = m_properties[GetPropertyIndex("width")].as_int * zoom;
    m_height = m_properties[GetPropertyIndex("height")].as_int * zoom;

    m_drawonscreen = !(m_x+m_width < 0 || m_y+m_height < 0 || m_x > g_winwidth || m_y > g_winheight);
}

void Instance::CheckMouseInput() {
    if(g_mouse->m_havebeenused) return;

    if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
    && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("WOW\n");
            printf("property count : %li\n", m_properties.size());

            g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_INSTANCE, this, "Instance"));
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            bool needcreation = true;
            for(unsigned int i = 0; i < leveditor->m_winmanager->GetWindowCount(); i++) {
                Window* win = leveditor->m_winmanager->Get(i);
                if(win->m_id == WINID_INSTANCEINFO) {
                    if(((InstanceInfoWindow*)win)->m_instanceptr == this) {
                        leveditor->m_winmanager->BringOnTop(win);
                        needcreation = false;
                        break;
                    }
                }
                    
            }
            if(needcreation) {
                leveditor->m_winmanager->Add(new InstanceInfoWindow(this));
            }
        }
        g_mouse->m_havebeenused = false;
    }

}

void Instance::Draw() {
    if(m_drawonscreen) {
        if(m_objtemplateptr->m_havetexture) {
            //get the textureobject from the objecttemplate
            TextureObject* textr = m_objtemplateptr->m_textureobj;
            DrawTexturePro(
                textr->m_texture,       //raylib texture
                {0, 0, (float)(textr->m_texture.width), (float)(textr->m_texture.height)},  //select all the texture
                {(float)m_x, (float)m_y, (float)m_width, (float)m_height},      //destination
                {0.0f, 0.0f},   //rotation center / center
                0.0f,           //rotation
                WHITE
            );
        }
        else {
            DrawRectangle(m_x, m_y, m_width, m_height, RED);
        }
    }
}

void Instance::Save(FILE* fileptr) {
    unsigned short objtemplateindex = m_parrent->m_parrent->m_objectmanager->GetIndex(m_objtemplateptr);

    WriteShort(fileptr, objtemplateindex);

    int propertycount = m_objtemplateptr->m_propertycount;

    //save all property values of the instance
    for(int i = 0; i < propertycount; i++) {
        
        int propertytype = GetProperty(i)->type;

        if(propertytype == OPT_INT) {   //property is int
            WriteInt(fileptr, m_properties[i].as_int);
        }
        else if(propertytype == OPT_STR) {  //property is str
            for(int j = 0; m_properties[i].as_str[j] != 0; j++) {
                putc(m_properties[i].as_str[j], fileptr);
            }
            putc(0, fileptr);   //null-terminator
        }
    }
}


void Instance::MoveTo(int x, int y) {
    m_properties[GetPropertyIndex("x")].as_int = x;
    m_properties[GetPropertyIndex("y")].as_int = y;
}


int Instance::GetPropertyIndex(std::string propertyname) {
    return m_objtemplateptr->GetPropertyIndex(propertyname);
}

ObjectProperty* Instance::GetProperty(int index) {
    return m_objtemplateptr->GetProperty(index);
}