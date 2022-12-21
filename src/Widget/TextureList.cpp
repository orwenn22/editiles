#include "TextureList.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/WindowManager.h"
#include "../TextureManager/TextureManager.h"
#include "../TextureManager/TextureObject.h"
#include "../Windows/Texture/TextureInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>

TextureList::TextureList(int x, int y, int w, int h, Editor* editor) : ElementList(x, y, w, h) {
    m_firstelementindex = 0;
    m_canselectelement = false;
    m_elementheight = 30;

    m_editor = editor;
}


void TextureList::RightClickOn(int clickindex) {
    printf("right click on index %i, texture address %p\n", clickindex, m_editor->m_texturemanager->Get(clickindex));
    bool needcreation = true;

    for(unsigned int i = 0; i < m_editor->m_winmanager->m_wincount; i++) {
        Window* win = m_editor->m_winmanager->Get(i);
        if(win->m_id == WINID_TEXTUREINFO) {
            if(((TextureInfoWindow*)win)->m_textureobjectptr == m_editor->m_texturemanager->Get(clickindex)) {
                //the window already exist
                m_editor->m_winmanager->BringOnTop(win);
                needcreation = false;
                break;
            }
        }
    }
    if(needcreation) {
        m_editor->m_winmanager->Add(new TextureInfoWindow(m_editor->m_texturemanager->Get(clickindex)));
    }
}

void TextureList::LeftClickOn(int clickindex) {
    TextureObject* textrptr = m_editor->m_texturemanager->Get(clickindex);
    printf("left click on index %i, texture address %p\n", clickindex, textrptr);
    g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_TEXTURE, textrptr, TextFormat("Texture %p", textrptr)));
}


void TextureList::DrawElement(int painterx, int paintery, int elementindex) {
        //label
        if(m_editor->m_texturemanager->Get(elementindex)->m_name.empty()) {
            DrawText("[no name]", painterx+3, paintery+10, 10, WHITE);
        } else {
            DrawText(m_editor->m_texturemanager->Get(elementindex)->m_name.c_str(), painterx+3, paintery+10, 10, WHITE);
        }

}

int TextureList::GetElementCount() {
    return m_editor->m_texturemanager->m_texturecount;
}

void TextureList::PreInputCheck() {
    //Drag and drop file to list            
    if(g_mouse->m_havefiles) {
        if(g_mouse->m_fileslist.count == 1) {
            TextureObject* newtxtrobj =  new TextureObject(g_mouse->m_fileslist.paths[0], "Imported Texture");
            if(newtxtrobj->m_texture.id <= 0) {     //loading failure
                delete newtxtrobj;
            } else {    //success
                m_editor->m_texturemanager->Add(newtxtrobj);
            }
        }
    }
}