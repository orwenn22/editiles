#include "Palette.h"

#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Themes/ColorTheme.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerIDs.h"
#include "../Level.h"
#include "../TextureManager/TextureObject.h"

#include <raylib.h>

Palette::Palette(int x, int y, int w, int h, Editor* editor) : Widget(x, y, w, h) {
    m_firstelement = 0;
    m_zoom = 1;

    m_editor = editor;
}

void Palette::Update() {
    Level* level = m_editor->m_level;

    if(g_mouse->m_havebeenused) return;

    Layer* selectedlayer = level->GetLayer(level->m_selectedlayer);
    if(selectedlayer == NULL) return;

    if(selectedlayer->m_havetexture == false) return;
    TextureObject* textrobj = selectedlayer->m_textureobj;

    if(selectedlayer->m_type == LAYERID_GRID) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            if(IsKeyDown(KEY_LEFT_CONTROL)) {   //zoom
                m_zoom += (int) GetMouseWheelMove();

                if(m_zoom <= 0) {
                    m_zoom = 1;
                }
            } else {    //scroll
                    int tilecountx = (m_width-2) / (level->m_boxwidth * m_zoom);

                m_firstelement -= (int) GetMouseWheelMove() * tilecountx;

                if(m_firstelement < 0) {
                    m_firstelement = 0;
                }
            }
            //click
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                //calculate the number of tiles vertivaly and horizontaly
                int tilecountx = (m_width-2) / (textrobj->m_tilewidth * m_zoom);
                int tilecounty = (m_height-2) / (textrobj->m_tileheight * m_zoom);

                //calculate the position of the clicked tile
                int tileclickx = (g_mouse->m_x - m_x-1) / (textrobj->m_tilewidth * m_zoom);
                int tileclicky = (g_mouse->m_y - m_y-1) / (textrobj->m_tileheight * m_zoom);

                //check if the values are correct
                if(tileclickx < tilecountx && tileclicky < tilecounty) {
                    //calculate the index
                    int clickindex = tileclickx + tileclicky*tilecountx;
                    clickindex+= m_firstelement;

                    //apply selection
                    printf("Palette.cpp : clicked: %i\n", clickindex);
                    level->m_selectednumber = clickindex;
                }
            }
        }
    }
}

void Palette::Draw() {
    Level* level = m_editor->m_level;
    
    Layer* selectedlayer = level->GetLayer(level->m_selectedlayer);
    bool layerexist;
    if(selectedlayer == NULL) {
        layerexist = false;
    }
    else {
        layerexist = true;
    }
   
    if(layerexist) {
        if(selectedlayer->m_type == LAYERID_GRID) {
            if(selectedlayer->m_havetexture) {
                DrawTiles(selectedlayer);
            }
            else {
                DrawText("The selected layer don't have a texture :(", m_x+5, m_y+5, 10, RED);
            }
        }
        else {
            DrawText("The selected layer is not a Tile Layer :(", m_x+5, m_y+5, 10, RED);
        }
    }
    else {
        DrawText("There is no layer in the level :(", m_x+5, m_y+5, 10, RED);
    }

    //widget outline
    DrawRectangleLines(m_x, m_y, m_width, m_height, g_colortheme.OutlineColor);
}

void Palette::DrawTiles(Layer* layer) {
    Level* level = layer->m_parrent;

    TextureObject* textrobj = layer->m_textureobj;
    int tilecountx = (m_width-2) / (textrobj->m_tilewidth * m_zoom);
    int tilecounty = (m_height-2) / (textrobj->m_tileheight * m_zoom);

    //tiles
    for(int y = 0; y < tilecounty; y++) {
        for(int x = 0; x < tilecountx; x++) {
            textrobj->DrawTile(
                (m_x+1) + x * (textrobj->m_tilewidth * m_zoom),
                (m_y+1) + y * (textrobj->m_tileheight * m_zoom),
                x + y*tilecountx + m_firstelement,
                m_zoom
            );
            //printf("drawindex: %i\n", x + y*tilecounty + m_firstelement);
        }
    }

    //selection outline
    if(level->m_selectednumber >= m_firstelement
    && level->m_selectednumber < m_firstelement + tilecountx*tilecounty) {
        int positiontooutline = level->m_selectednumber - m_firstelement;
        DrawRectangleLines(
            (m_x+1) + (positiontooutline%tilecountx) * (textrobj->m_tilewidth * m_zoom),
            (m_y+1) + (positiontooutline/tilecountx) * (textrobj->m_tileheight * m_zoom),
            (textrobj->m_tilewidth * m_zoom),
            (textrobj->m_tileheight * m_zoom),
            GREEN
        );
    }
}