#include "ObjectList.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../GUI/Mouse/DragAndDropObject.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Themes/ColorTheme.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../ObjectManager/ObjectManager.h"
#include "../ObjectManager/ObjectTemplate.h"
#include "../ParseFunctions.h"
#include "../TextureManager/TextureManager.h"
#include "../Windows/Object/ObjectInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>


ObjectList::ObjectList(int x, int y, int w, int h, Editor* editor) : ElementList(x, y, w, h) {
    m_elementheight = 30;
    m_canselectelement = false;

    m_editor = editor;
}

void ObjectList::RightClickOn(int clickindex) {
    ObjectTemplate* objptr = m_editor->m_level->m_objectmanager->Get(clickindex);
    bool needcreation = true;

    for(unsigned int i = 0; i < m_editor->m_winmanager->m_wincount; i++) {
        Window* win = m_editor->m_winmanager->Get(i);
        if(win->m_id == WINID_OBJECTINFO) {
            if(((ObjectInfoWindow*)win)->m_objptr == objptr) {
                needcreation = false;
                m_editor->m_winmanager->BringOnTop(win);
            }
        }
    }

    if(needcreation) {
        m_editor->m_winmanager->Add(new ObjectInfoWindow(objptr, m_editor));
    }
}

void ObjectList::LeftClickOn(int clickindex) {
    ObjectTemplate* objptr = m_editor->m_level->m_objectmanager->Get(clickindex);
    DragAndDropObject dndobj = DragAndDropObject(DRAG_OBJECT_OBJECTTEMPLATE, objptr, TextFormat("Object %s", objptr->m_name.c_str()));

    g_mouse->GiveDragObject(dndobj);
}

void ObjectList::LeftReleaseOn(int releaseindex) {
    ObjectTemplate* objptr = m_editor->m_level->m_objectmanager->Get(releaseindex);

    if(g_mouse->m_havedragobject /* && g_mouse->m_havebeenused == false */) {
        if(g_mouse->m_dragobject.m_type == DRAG_OBJECT_TEXTURE) {       //verify if the texture don't come from another tab
            TextureObject* txtrobj = (TextureObject*)(g_mouse->m_dragobject.m_data.as_ptr);
            
            if(m_editor->m_texturemanager->GetIndex(txtrobj) != -1) {
                objptr->m_havetexture = true;
                objptr->m_textureobj = (TextureObject*)(g_mouse->m_dragobject.m_data.as_ptr);
            }
        }
    }
}

void ObjectList::DrawElement(int painterx, int paintery, int elementindex) {
    DrawText(m_editor->m_level->m_objectmanager->Get(elementindex)->m_name.c_str(), painterx+3, paintery+10, 10, g_colortheme->TextColor);
}

int ObjectList::GetElementCount() {
    return m_editor->m_level->m_objectmanager->m_objectcount;
}

void ObjectList::PreInputCheck() {
    Level* level = m_editor->m_level;
    //Drag and drop file to list
    if(g_mouse->m_havefiles) {
        if(g_mouse->m_fileslist.count == 1) {
            printf("ObjectList : receiving something\n");
            //FIXME: handle this in a better way
            ObjectManager* newobjmanager = ParseOBJTBFile(g_mouse->m_fileslist.paths[0]);

            if(newobjmanager != NULL) {     ///newobjmanager is valid
                if(level->m_objectmanager->m_objectcount == 0) {    //no object in current manager
                    printf("ObjectList : yay\n");
                    delete level->m_objectmanager;
                    level->m_objectmanager = newobjmanager;
                }
                else {
                    printf("Object list : can't load table because current one not empty :(\n");
                    delete newobjmanager;
                }
                
            }
            else {
                ObjectTemplate* newobj = ParseOBJFile(g_mouse->m_fileslist.paths[0]);
                if(newobj != NULL) {
                    printf("ObjectList : yay\n");
                    int err = level->m_objectmanager->Add(newobj);
                    if(err != 0) delete newobj;
                }
                else {
                    printf("ObjectList : Not an object ?\n");
                }
            }
        }
    }
}