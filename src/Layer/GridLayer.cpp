#include "GridLayer.h"

#include "../FileUtil/FileUtil.h"
#include "../GUI/MainWindow.h"
#include "../Level.h"
#include "../TextureManager/TextureObject.h"
#include "LayerIDs.h"

#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>


GridLayer::GridLayer(short gridwidth, short gridheight, std::string name) : Layer(name) {
    m_type = LAYERID_GRID;

    m_width = gridwidth;
    m_height = gridheight;
    m_boxwidth = 16;
    m_boxheight = 16;

    m_griddata = (unsigned short*) malloc(sizeof(unsigned short) * gridwidth * gridheight);

    for(int i = 0; i < m_width * m_height; i++) {
        m_griddata[i] = 0;
    }
    printf("allocated grid\n");

    m_tilemapname = "";
}

GridLayer::~GridLayer() {
    free(m_griddata);
    printf("unallocated grid\n");
}

void GridLayer::Draw(int x, int y) {
    unsigned char zoom = m_parrent->m_zoom;

    int firstxbox = -x / (m_boxwidth * zoom);
    int firstybox = -y / (m_boxheight * zoom);

    if(firstxbox < 0) firstxbox = 0;
    if(firstybox < 0) firstybox = 0;

    int lastxbox = firstxbox + (g_winwidth  / (m_boxwidth * zoom) ) + 2;
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

    int lastxbox = firstxbox + (g_winwidth / (m_boxwidth * zoom)) + 2;
    int lastybox = firstybox + (g_winheight / (m_boxheight * zoom)) + 2;

    if(firstxbox < 0) firstxbox = 0;
    if(firstybox < 0) firstybox = 0;

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

void GridLayer::SetBoxSize(unsigned short width, unsigned short height) {
    m_boxwidth = width;
    m_boxheight = height;
}

void GridLayer::SetBoxValue(unsigned int xpos, unsigned int ypos, unsigned short value) {
    if(xpos >= 0 && xpos < m_width
    && ypos >= 0 && ypos < m_height) {
        m_griddata[ypos*m_width+xpos] = value;
    }
}

unsigned short GridLayer::GetBoxValue(unsigned int xpos, unsigned int ypos) {
    if(xpos >= 0 && xpos < m_width
    && ypos >= 0 && ypos < m_height) {
        return m_griddata[ypos*m_width+xpos];
    }
    return -1;  //out of grid
}

void GridLayer::Save(FILE* fileptr) {
    Layer::Save(fileptr);   //Layer type and name

    SaveGridData(fileptr);
}

void GridLayer::SaveStandalone() {
    std::string filename = m_name + ".tlmp";
    FILE* exportfile = fopen(filename.c_str(), "w");

    fputs("tlmp", exportfile);          //file signature
    WriteShort(exportfile, m_width);    //tilemap width
    WriteShort(exportfile, m_height);   //tilemap height
    // //Maybe it would be better to also export the width and height of a tile ?
    // WriteShort(exportfile, m_boxwidth);      //tile width
    // WriteShort(exportfile, m_boxwidth);      //tile height

    Save(exportfile);

    fclose(exportfile);
}

void GridLayer::SaveGridData(FILE* fileptr) {
    //tilemap name
    fputs(m_tilemapname.c_str(), fileptr);
    putc(0, fileptr);

    //actual layer data
    int datalen = m_width*m_height;
    for(int i = 0; i < datalen; i++) {
        WriteShort(fileptr, m_griddata[i]);
    }
}