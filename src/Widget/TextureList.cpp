#include "TextureList.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../GUI/WindowManager.h"
#include "../Mouse/MouseObject.h"
#include "../TextureManager/TextureManager.h"
#include "../TextureManager/TextureObject.h"
#include "../Windows/TextureInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <raylib.h>

extern int g_maxfps;

extern MouseObject* g_mouse;
extern Editor* g_editor;

TextureList::TextureList(WidgetManager* wm, int x, int y, int w, int h) : Widget(wm, x, y, w, h) {
    m_firstelementindex = 0;
}

void TextureList::Update() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            //Drag and drop file to list            
            if(g_mouse->m_havefiles) {
                if(g_mouse->m_fileslist.count == 1) {
                    TextureObject* newtxtrobj =  new TextureObject(g_mouse->m_fileslist.paths[0], "Imported Texture");
                    if(newtxtrobj->m_texture.id <= 0) {     //loading failure
                        delete newtxtrobj;
                    } else {    //success
                        g_editor->m_texturemanager->Add(newtxtrobj);
                    }
                }
            }
            
            //Click
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                int clickindex = (g_mouse->m_y-m_y)/30 + m_firstelementindex;
                if(clickindex < g_editor->m_texturemanager->m_texturecount) {
                    printf("right click on index %i, texture address %p\n", clickindex, g_editor->m_texturemanager->Get(clickindex));

                    bool needcreation = true;

                    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
                        Window* win = g_editor->m_winmanager->Get(i);
                        if(win->m_id == WINID_TEXTUREINFO) {
                            if(((TextureInfoWindow*)win)->m_textureobjectptr == g_editor->m_texturemanager->Get(clickindex)) {
                                //the window already exist
                                g_editor->m_winmanager->BringOnTop(win);
                                needcreation = false;
                                break;
                            }
                        }
                    }
                    if(needcreation) {
                        g_editor->m_winmanager->Add(new TextureInfoWindow(g_editor->m_winmanager ,g_editor->m_texturemanager->Get(clickindex)));
                    }
                }
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int clickindex = (g_mouse->m_y-m_y)/30 + m_firstelementindex;
                if(clickindex < g_editor->m_texturemanager->m_texturecount) {
                    TextureObject* textrptr = g_editor->m_texturemanager->Get(clickindex);
                    printf("left click on index %i, texture address %p\n", clickindex, textrptr);
                    g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_TEXTURE, textrptr, TextFormat("Texture %p", textrptr)));
                }
            }

            //scroll
            m_firstelementindex-= (int)GetMouseWheelMove();

            g_mouse->m_havebeenused = true;
        }
    }


    if(m_firstelementindex >= g_editor->m_texturemanager->m_texturecount) {
        m_firstelementindex = g_editor->m_texturemanager->m_texturecount-1;
    }
    if(m_firstelementindex < 0) {
        m_firstelementindex = 0;
    }
}

void TextureList::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);
    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);


    int painterx = m_x;
    int paintery = m_y;
    for(int i = m_firstelementindex; (i < g_editor->m_texturemanager->m_texturecount) && (i < m_firstelementindex + (m_height/30)); i++) {
        //label
        if(g_editor->m_texturemanager->Get(i)->m_name.empty()) {
            DrawText("[no name]", painterx+3, paintery+10, 10, WHITE);
        } else {
            DrawText(g_editor->m_texturemanager->Get(i)->m_name.c_str(), painterx+3, paintery+10, 10, WHITE);
        }
        DrawLine(m_x, paintery+29, m_x+m_width-6, paintery+29, WHITE);
        paintery += 30;
    }

    DrawLine(m_x+m_width-6, m_y, m_x+m_width-6, m_y+m_height, WHITE);

    //scrollbar
    if(g_editor->m_texturemanager->m_texturecount > 0) {
        int scrollbarx = m_x+m_width-4;
        int scrollbary = m_y+2+(((m_height-4)/g_editor->m_texturemanager->m_texturecount))*m_firstelementindex;
        
        //                                                                              V number of elements that can be displayed
        int scrollbarheight = ((m_height-4)/g_editor->m_texturemanager->m_texturecount)*(m_height/30);

        if(scrollbary+scrollbarheight>m_y+m_height-2) {
            scrollbarheight = (m_y+m_height-2) - scrollbary;    //don't cross the bottom of the scrollbar area
        }

        DrawRectangle(scrollbarx, scrollbary, 2, scrollbarheight, WHITE);
    }
}