#include "Level.h"

#include "Editor.h"
#include "GUI/Mouse/MouseObject.h"
#include "Layer/GridLayer.h"
#include "Layer/Layer.h"
#include "Layer/LayerIDs.h"
#include "ObjectManager/ObjectManager.h"
//#include "ObjectManager/ObjectTemplate.h"

#include <raylib.h>
#include <stdio.h>

extern int g_winwidth;
extern int g_winheight;

extern MouseObject* g_mouse;

Level::Level() {
    m_boxwidth = 16;
    m_boxheight = 16;
    m_width = 16;
    m_height = 16;

    m_x = 10;
    m_y = 10;

    m_zoom = 1;

    m_followmouse = false;

    int m_relativemouseposx = 0;
    int m_relativemouseposy = 0;

    int m_overredboxx = 0;
    int m_overredboxy = 0;

    m_layercount = 0;
    AddLayer("Default layer");
    m_selectedlayer = 0;

    m_selectednumber = 1;
    m_ispainting = false;

    m_objectmanager = new ObjectManager(this);
}

Level::Level(int width, int height, int boxwidth, int boxheight) {
    m_width = width;
    m_height = height;
    m_boxwidth = boxwidth;
    m_boxheight = boxheight;

    //printf("BoxWidth: %i\n", m_boxwidth);

    m_x = 10;
    m_y = 10;

    m_zoom = 1;

    m_followmouse = false;

    int m_relativemouseposx = 0;
    int m_relativemouseposy = 0;

    int m_overredboxx = 0;
    int m_overredboxy = 0;


    m_layercount = 0;
    AddLayer("Default layer");
    m_selectedlayer = 0;

    m_selectednumber = 1;
    m_ispainting = false;

    m_objectmanager = new ObjectManager(this);
    //m_objectmanager->Add(new ObjectTemplate("MyObject"));
}

Level::~Level() {
    delete m_objectmanager;
    int vecsize = m_layers.size();
    for(int i = 0; i < vecsize; i++) {
        delete m_layers[i];
    }
    m_layers.clear();
    m_layercount = 0;
    m_selectedlayer = -1;
}

void Level::Update() {
    //selected layer
    if(m_selectedlayer >= m_layercount) {
        m_selectedlayer = m_layercount - 1;
    }
    if(m_selectedlayer == -1 && m_layercount >= 1) {
        m_selectedlayer = 0;
    }
    /////////////////

    // DRAG & DROP
    if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && g_mouse->m_havebeenused == false) {
        m_xmouseoffset = m_x - g_mouse->m_x;
        m_ymouseoffset = m_y - g_mouse->m_y;

        m_followmouse = true;
    }

    if(m_followmouse) {
        m_x = g_mouse->m_x + m_xmouseoffset;
        m_y = g_mouse->m_y + m_ymouseoffset;
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
        m_followmouse = false;
    }
    ////////////////

    //overring stuff
    m_relativemouseposx = g_mouse->m_x - m_x;
    m_relativemouseposy = g_mouse->m_y - m_y;

    m_overredboxx = m_relativemouseposx / (m_boxwidth*m_zoom);
    m_overredboxy = m_relativemouseposy / (m_boxheight*m_zoom);

    if(m_relativemouseposx < 0) {
        m_overredboxx--;
    }
    if(m_relativemouseposy < 0) {
        m_overredboxy--;
    }
    //////////////////

    //Handle click  // painting
    if(g_mouse->m_havebeenused == false && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        m_ispainting = true;
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        m_ispainting = false;
    }

    if(m_ispainting) {
        //printf("%i %i\n", m_overredboxx, m_overredboxy);
        Layer* curlayer = GetLayer(m_selectedlayer);
        if(curlayer->m_type == LAYERID_GRID) {
            ((GridLayer*)curlayer)->SetBoxValue(m_overredboxx, m_overredboxy, m_selectednumber);
        }
    }
    ////////////////

    //Updating layers (?)
    int vecsize = m_layers.size();
    for(int i = 0; i < vecsize; i++) {
        m_layers[i]->Update();
    }
    ////////////////
}

void Level::Draw() {
    //draw all layers content
    //Layer 0 is on top
    //Layer 1 is behind
    //etc
    for(int i = m_layercount-1; i >= 0; i--) {
        m_layers[i]->Draw(m_x, m_y);
    }

    //draw grid
    if(m_layercount > 0) {
        int firstxbox = -m_x / (m_boxwidth * m_zoom);
        int firstybox = -m_y / (m_boxheight * m_zoom);
        if(firstxbox < 0) firstxbox = 0;
        if(firstybox < 0) firstybox = 0;

        int lastxbox = firstxbox + (g_winwidth  / (m_boxwidth * m_zoom) ) + 2;
        int lastybox = firstybox + (g_winheight / (m_boxheight * m_zoom)) + 2;
        if(lastxbox > m_width) lastxbox = m_width;
        if(lastybox > m_height) lastybox = m_height;

        for(int i = firstybox; i < lastybox; i++) { //Y
            for(int j = firstxbox; j < lastxbox; j++) { //X
                DrawRectangleLines(m_x + j * (m_boxwidth*m_zoom), m_y + i * (m_boxheight*m_zoom), m_boxwidth*m_zoom, m_boxheight*m_zoom, GRAY);
            }
        }
    
        GetLayer(m_selectedlayer)->DrawNumbers(m_x, m_y);
    }

    //red outline around level
    DrawRectangleLines(m_x, m_y, m_boxwidth * m_width * m_zoom, m_boxheight * m_height * m_zoom, RED);

    //green cursor on the mouse
    if(g_mouse->m_havebeenused == false) {
        DrawRectangleLines(
            m_x + m_overredboxx * m_boxwidth * m_zoom,      //AKA m_x * totalboxwidth
            m_y + m_overredboxy * m_boxheight * m_zoom,     //AKA m_y * totalboxheight
            m_boxwidth * m_zoom,
            m_boxheight * m_zoom,
            GREEN
        );
    }
}

void Level::AddLayer(std::string name) {
    GridLayer* newlayer = new GridLayer(m_width, m_height, this);
    newlayer->SetBoxSize(m_boxwidth, m_boxheight);
    newlayer->m_name = name;

    m_layers.push_back(newlayer);
    m_layercount++;
}

Layer* Level::GetLayer(int index) {
    if(index >= 0 && index < m_layercount) {
        return m_layers[index];
    }
    return NULL;
}

void Level::RemoveLayer(Layer* layerptr) {
    for(int i = 0; i < m_layercount; i++) {
        if(m_layers[i] == layerptr) {
            delete m_layers[i];
            m_layers.erase(m_layers.begin() + i);
            m_layercount--;
            return;
        }
    }
}

void Level::SwapLayers(int index1, int index2) {
    if(index1 >= 0 && index1 < m_layercount
    && index2 >= 0 && index2 < m_layercount) {
        Layer* temp = GetLayer(index1);
        m_layers[index1] = GetLayer(index2);
        m_layers[index2] = temp;
    }
}