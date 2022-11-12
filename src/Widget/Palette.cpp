#include "Palette.h"

#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../Layer/Layer.h"
#include "../Layer/LayerIDs.h"
#include "../Level.h"
#include "../TextureManager/TextureObject.h"

#include <raylib.h>

extern Editor* g_editor;

Palette::Palette(int x, int y, int w, int h) : Widget(x, y, w, h) {
    m_firstelement = 0;
    m_zoom = 1;
}

void Palette::Update() {
    if(g_mouse->m_havebeenused == false) {
        Layer* selectedlayer = g_editor->m_level->GetLayer(g_editor->m_level->m_selectedlayer);

        if(selectedlayer->m_type == LAYERID_GRID) {
            if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
            && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
                if(IsKeyDown(KEY_LEFT_CONTROL)) {   //zoom
                    m_zoom += (int) GetMouseWheelMove();

                    if(m_zoom <= 0) {
                        m_zoom = 1;
                    }
                } else {    //scroll
                    int tilecountx = (m_width-2) / (g_editor->m_level->m_boxwidth * m_zoom);

                    m_firstelement -= (int) GetMouseWheelMove() * tilecountx;

                    if(m_firstelement < 0) {
                        m_firstelement = 0;
                    }
                }
                //click
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    //calculate the number of tiles vertivaly and horizontaly
                    int tilecountx = (m_width-2) / (g_editor->m_level->m_boxwidth * m_zoom);
                    int tilecounty = (m_height-2) / (g_editor->m_level->m_boxheight * m_zoom);

                    //calculate the position of the clicked tile
                    int tileclickx = (g_mouse->m_x - m_x-1) / (g_editor->m_level->m_boxwidth * m_zoom);
                    int tileclicky = (g_mouse->m_y - m_y-1) / (g_editor->m_level->m_boxheight * m_zoom);

                    //check if the values are correct
                    if(tileclickx < tilecountx && tileclicky < tilecounty) {
                        //calculate the index
                        int clickindex = tileclickx + tileclicky*tilecountx;
                        clickindex+= m_firstelement;

                        //apply selection
                        printf("clicked: %i\n", clickindex);
                        g_editor->m_level->m_selectednumber = clickindex;
                    }
                }
            }
        }
    }
}

void Palette::Draw() {
    Layer* selectedlayer = g_editor->m_level->GetLayer(g_editor->m_level->m_selectedlayer);

    if(selectedlayer->m_type == LAYERID_GRID) {
        if(selectedlayer->m_havetexture) {
            TextureObject* textrobj = selectedlayer->m_textureobj;
            int tilecountx = (m_width-2) / (g_editor->m_level->m_boxwidth * m_zoom);
            int tilecounty = (m_height-2) / (g_editor->m_level->m_boxheight * m_zoom);

            //tiles
            for(int y = 0; y < tilecounty; y++) {
                for(int x = 0; x < tilecountx; x++) {
                    textrobj->DrawTile(
                        (m_x+1) + x * (g_editor->m_level->m_boxwidth * m_zoom),
                        (m_y+1) + y * (g_editor->m_level->m_boxheight * m_zoom),
                        x + y*tilecountx + m_firstelement,
                        m_zoom
                    );
                    //printf("drawindex: %i\n", x + y*tilecounty + m_firstelement);
                }
            }

            //selection outline
            if(g_editor->m_level->m_selectednumber >= m_firstelement
            && g_editor->m_level->m_selectednumber < m_firstelement + tilecountx*tilecounty) {
                int positiontooutline = g_editor->m_level->m_selectednumber - m_firstelement;
                DrawRectangleLines(
                    (m_x+1) + (positiontooutline%tilecountx) * (g_editor->m_level->m_boxwidth * m_zoom),
                    (m_y+1) + (positiontooutline/tilecountx) * (g_editor->m_level->m_boxheight * m_zoom),
                    (g_editor->m_level->m_boxwidth * m_zoom),
                    (g_editor->m_level->m_boxheight * m_zoom),
                    GREEN
                );
            }
        }
        else {
            DrawText("The selected layer don't have a texture :(", m_x+5, m_y+5, 10, RED);
        }
    }
    else {
        DrawText("The selected layer is not a Tile Layer :(", m_x+5, m_y+5, 10, RED);
    }

    //widget outline
    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);
}