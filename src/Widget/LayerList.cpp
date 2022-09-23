#include "LayerList.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../Layer/Layer.h"
#include "../GUI/Window.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../Mouse/DragAndDropObject.h"
#include "../Mouse/MouseObject.h"
#include "../Windows/LayerInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <stdio.h>

extern Editor* g_editor;
extern MouseObject* g_mouse;

LayerList::LayerList(WidgetManager* widgetmanager, int x, int y, int w, int h) : Widget(widgetmanager, x, y, w, h) {
    m_firstelementindex = 0;
}


void LayerList::Update() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            //Click
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                int clickindex = (g_mouse->m_y-m_y)/30 + m_firstelementindex;
                if(clickindex < g_editor->m_level->m_layercount) {
                    printf("right click on index %i, layer address %p\n", clickindex, g_editor->m_level->GetLayer(clickindex));

                    bool needcreation = true;   //does the window need to be created ?

                    for(int i = 0; i < g_editor->m_winmanager->m_wincount; i++) {
                        Window* win = g_editor->m_winmanager->Get(i);
                        if(win->m_id == WINID_LAYERINFO) {      //the window exist
                            if(((LayerInfoWindow*)win)->m_layerpointer == g_editor->m_level->GetLayer(clickindex)) {
                                //the window already exist
                                g_editor->m_winmanager->BringOnTop(win);
                                needcreation = false;
                                break;
                            }
                        }
                    }
                    if(needcreation) {      //the window don't exist
                        g_editor->m_winmanager->Add(new LayerInfoWindow(g_editor->m_winmanager ,g_editor->m_level->GetLayer(clickindex)));
                    }
                }
            }

            //Drag&drop with left click
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int clickindex = (g_mouse->m_y-m_y)/30 + m_firstelementindex;
                if(clickindex < g_editor->m_level->m_layercount) {
                    printf("left click on index %i, layer address %p\n", clickindex, g_editor->m_level->GetLayer(clickindex));
                    g_editor->m_level->m_selectedlayer = clickindex;

                    //for layer d&d
                    g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_LAYER, clickindex, "Layer " + g_editor->m_level->GetLayer(clickindex)->m_name));
                }
            }

            //recieve drag and drop object
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && g_mouse->m_havedragobject) {
                int recieveindex = (g_mouse->m_y-m_y)/30 + m_firstelementindex;
                if(recieveindex < g_editor->m_level->m_layercount) {
                    //type layer
                    if(g_mouse->m_dragobject.m_type == 1) {
                        printf("swapping %i and %i\n", recieveindex, g_mouse->m_dragobject.m_data.as_int);
                        g_editor->m_level->SwapLayers(recieveindex, g_mouse->m_dragobject.m_data.as_int);
                        g_editor->m_level->m_selectedlayer = recieveindex;
                    }
                    //type texture
                    else if(g_mouse->m_dragobject.m_type == 2) {
                        g_editor->m_level->GetLayer(recieveindex)->m_havetexture = true;
                        g_editor->m_level->GetLayer(recieveindex)->m_textureobj = (TextureObject*) g_mouse->m_dragobject.m_data.as_ptr;
                    }
                }
            }

            //scroll
            m_firstelementindex-= (int)GetMouseWheelMove();

            g_mouse->m_havebeenused = true;
        }
    }

    if(m_firstelementindex >= g_editor->m_level->m_layercount) {
        m_firstelementindex = g_editor->m_level->m_layercount-1;
    }
    
    if(m_firstelementindex < 0) {
        m_firstelementindex = 0;
    }
}

void LayerList::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);
    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);


    int painterx = m_x;
    int paintery = m_y;
    for(int i = m_firstelementindex; (i < g_editor->m_level->m_layercount) && (i < m_firstelementindex + (m_height/30)); i++) {
        //label
        if(g_editor->m_level->GetLayer(i)->m_name.empty()) {
            DrawText("[no name]", painterx+3, paintery+10, 10, WHITE);
        } else {
            DrawText(g_editor->m_level->GetLayer(i)->m_name.c_str(), painterx+3, paintery+10, 10, WHITE);
        }

        //separator
        DrawLine(m_x, paintery+29, m_x+m_width-6, paintery+29, WHITE);
        paintery += 30;
    }

    //outline arount selected layer
    //                                                                                                   g_editor->m_level->m_layercount      
    if(g_editor->m_level->m_selectedlayer >= m_firstelementindex && g_editor->m_level->m_selectedlayer < m_firstelementindex+(m_height/30)) {
        int yorigin = (g_editor->m_level->m_selectedlayer - m_firstelementindex) * 30 + 2;
        DrawRectangleLines(m_x+2, m_y+yorigin, m_width-10, 25, RED);
    }

    //vertical line
    DrawLine(m_x+m_width-6, m_y, m_x+m_width-6, m_y+m_height, WHITE);

    //scrollbar
    if(g_editor->m_level->m_layercount > 0) {
        int scrollbarx = m_x+m_width-4;
        int scrollbary = m_y+2+(((m_height-4)/g_editor->m_level->m_layercount))*m_firstelementindex;
        
        //                                                                              V number of elements that can be displayed
        int scrollbarheight = ((m_height-4)/g_editor->m_level->m_layercount)*(m_height/30);

        if(scrollbary+scrollbarheight>m_y+m_height-2) {
            scrollbarheight = (m_y+m_height-2) - scrollbary;    //don't cross the bottom of the scrollbar area
        }

        DrawRectangle(scrollbarx, scrollbary, 2, scrollbarheight, WHITE);
    }
}