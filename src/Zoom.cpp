#include "Zoom.h"

#include "Editor.h"
#include "Level.h"

extern Editor* g_editor;

void Zoom(int relativezoom, int zoomxcenter, int zoomycenter) {
    if(g_editor->m_havelevel == false) {
        return;
    }
    
    if(g_editor->m_level->m_zoom + relativezoom < 1) {  //TODO : handle this correctly
        return;
    }

    //calculate distance between zoom center and grid's top left
    float distancex = (float)(g_editor->m_level->m_x - zoomxcenter);
    float distancey = (float)(g_editor->m_level->m_y - zoomycenter);

    //"cancel" old zoom and apply new zoom
    float currentzoom = (float) g_editor->m_level->m_zoom;
    distancex = (distancex / currentzoom) * (currentzoom+(float)relativezoom);
    distancey = (distancey / currentzoom) * (currentzoom+(float)relativezoom);

    //apply new position
    g_editor->m_level->m_x = zoomxcenter + (int)distancex;
    g_editor->m_level->m_y = zoomycenter + (int)distancey;

    //apply new zoom to grid
    g_editor->m_level->m_zoom += relativezoom;
}