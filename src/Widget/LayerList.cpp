#include "LayerList.h"

#include "../DragObjectIDs.h"
#include "../Editor.h"
#include "../Layer/Layer.h"
#include "../GUI/Mouse/DragAndDropObject.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Window.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../Windows/Layer/LayerInfoWindow.h"
#include "../Windows/WinIDs.h"

#include <stdio.h>

extern Editor* g_editor;

LayerList::LayerList(WidgetManager* widgetmanager, int x, int y, int w, int h) : ElementList(widgetmanager, x, y, w, h) {
    m_firstelementindex = 0;
    m_canselectelement = true;
    m_elementheight = 30;
}



void LayerList::RightClickOn(int clickindex) {
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


void LayerList::LeftClickOn(int clickindex) {
    printf("left click on index %i, layer address %p\n", clickindex, g_editor->m_level->GetLayer(clickindex));
    g_editor->m_level->m_selectedlayer = clickindex;

    //for layer d&d
    g_mouse->GiveDragObject(DragAndDropObject(DRAG_OBJECT_LAYER, clickindex, "Layer " + g_editor->m_level->GetLayer(clickindex)->m_name));

}

void LayerList::LeftReleaseOn(int releaseindex) {
    //type layer
    if(g_mouse->m_dragobject.m_type == 1) {
        printf("swapping %i and %i\n", releaseindex, g_mouse->m_dragobject.m_data.as_int);
        g_editor->m_level->SwapLayers(releaseindex, g_mouse->m_dragobject.m_data.as_int);
        g_editor->m_level->m_selectedlayer = releaseindex;
    }
    //type texture
    else if(g_mouse->m_dragobject.m_type == 2) {
        g_editor->m_level->GetLayer(releaseindex)->m_havetexture = true;
        g_editor->m_level->GetLayer(releaseindex)->m_textureobj = (TextureObject*) g_mouse->m_dragobject.m_data.as_ptr;
    }
}

void LayerList::DrawElement(int painterx, int paintery, int elementindex) {
    if(g_editor->m_level->GetLayer(elementindex)->m_name.empty()) {
        DrawText("[no name]", painterx+3, paintery+10, 10, WHITE);
    } else {
        DrawText(g_editor->m_level->GetLayer(elementindex)->m_name.c_str(), painterx+3, paintery+10, 10, WHITE);
    }
}

int LayerList::GetElementCount() {
    return g_editor->m_level->m_layercount;
}

int LayerList::GetSelectedElement() {
    return g_editor->m_level->m_selectedlayer;
}

void LayerList::SetSelectedElement(int newselection) {
    g_editor->m_level->m_selectedlayer = newselection;
}