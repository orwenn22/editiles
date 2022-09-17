#include "GridLayer.h"

#include "Level.h"
#include "TextureManager/TextureObject.h"

#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

extern int g_winwidth;
extern int g_winheight;


GridLayer::GridLayer(short gridwidth, short gridheight, Level* level) {
    m_parrent = level;

    m_griddata = (unsigned short*) malloc(sizeof(unsigned short) * gridwidth * gridheight);
    m_width = gridwidth;
    m_height = gridheight;

    m_boxwidth = 16;
    m_boxheight = 16;

    for(int i = 0; i < m_width * m_height; i++) {
        m_griddata[i] = 0;
    }
    printf("allocated grid\n");

    m_name = "Layer";

    m_havetexture = false;
}

GridLayer::~GridLayer() {
    free(m_griddata);
    printf("unallocated grid\n");
}

void GridLayer::Update() {

}

void GridLayer::Draw(int x, int y) {
    unsigned char zoom = m_parrent->m_zoom;

    int firstxbox = -x / (m_boxwidth * zoom);
    int firstybox = -y / (m_boxheight * zoom);

    if(firstxbox < 0) firstxbox = 0;
    if(firstybox < 0) firstybox = 0;

    int lastxbox = firstxbox + (g_winwidth / (m_boxwidth * zoom)) + 1;
    int lastybox = firstybox + (g_winheight / (m_boxheight * zoom)) + 2;

    if(lastxbox > m_width) lastxbox = m_width;
    if(lastybox > m_height) lastybox = m_height;


    //bool drawnumbers = ((m_boxwidth * zoom)>40);

    for(int i = firstybox; i < lastybox; i++) { //Y
        for(int j = firstxbox; j < lastxbox; j++) { //X
            if(m_havetexture) {
                m_textureobj->DrawTile(x + j * (m_boxwidth*zoom), y + i * (m_boxheight*zoom), m_griddata[i*m_width+j], zoom);
            }
            //if(drawnumbers) {
            //    DrawText(TextFormat("%i", m_griddata[i*m_width+j]),x + j * (m_boxwidth*zoom) +2, y + i * (m_boxheight*zoom) +2, 10, WHITE);
            //}
        }
    }
}

void GridLayer::DrawNumbers(int x, int y) {
    unsigned char zoom = m_parrent->m_zoom;

    int firstxbox = -x / (m_boxwidth * zoom);
    int firstybox = -y / (m_boxheight * zoom);

    if(firstxbox < 0) firstxbox = 0;
    if(firstybox < 0) firstybox = 0;

    int lastxbox = firstxbox + (g_winwidth / (m_boxwidth * zoom)) + 1;
    int lastybox = firstybox + (g_winheight / (m_boxheight * zoom)) + 2;

    if(lastxbox > m_width) lastxbox = m_width;
    if(lastybox > m_height) lastybox = m_height;


    bool drawnumbers = ((m_boxwidth * zoom)>40);

    if(drawnumbers)
    for(int i = firstybox; i < lastybox; i++) { //Y
        for(int j = firstxbox; j < lastxbox; j++) { //X
            DrawText(TextFormat("%i", m_griddata[i*m_width+j]),x + j * (m_boxwidth*zoom) +2, y + i * (m_boxheight*zoom) +2, 10, WHITE);
        }
    }
}

void GridLayer::SetBoxValue(unsigned int xpos, unsigned int ypos, unsigned short value) {
    if(xpos >= 0 && xpos < m_width
    && ypos >= 0 && ypos < m_height) {
        m_griddata[ypos*m_width+xpos] = value;
    }
}

void GridLayer::SetBoxSize(unsigned short width, unsigned short height) {
    m_boxwidth = width;
    m_boxheight = height;
}