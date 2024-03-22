#include "Editor.h"

#include "FileUtil/FileUtil.h"
#include "GUI/Mouse/MouseObject.h"
#include "GUI/WindowManager.h"
#include "Layer/GridLayer.h"
#include "Layer/Instance.h"
#include "Layer/InstanceLayer.h"
#include "Layer/LayerIDs.h"
#include "Level.h"
#include "ObjectManager/ObjectManager.h"
#include "ObjectManager/ObjectProperty.h"
#include "ObjectManager/ObjectTemplate.h"
#include "TextureManager/TextureManager.h"
#include "TextureManager/TextureObject.h"
#include "Windows/Layer/LayerListWindow.h"
#include "Windows/Object/ObjectListWindow.h"
#include "Windows/PaletteWindow.h"
#include "Windows/Texture/TextureListWindow.h"
#include "Windows/SaveWindow.h"
#include "Windows/WinIDs.h"
#include "Windows/ZoomWindow.h"

#include "ParseFunctions.h"

#include <raylib.h>

Editor::Editor() {
    m_app = NULL;

    m_name = "Untitled";
    
    m_havelevel = false;
    m_level = NULL;

    m_texturemanager = new TextureManager(this);

    m_winmanager = new WindowManager();
    //m_winmanager->Add(new Window(m_winmanager));
}

Editor::Editor(int lvlwidth, int lvlheight, int tilewidth, int tileheight) : Editor() {
    CreateNewLevel(lvlwidth, lvlheight, tilewidth, tileheight);
}

Editor::Editor(std::string filename) : Editor() {
    LoadFromFile(filename.c_str());
}


Editor::~Editor() {
    if(m_havelevel) {
        delete m_level;
    }
    delete m_texturemanager;
    delete m_winmanager;
}

void Editor::Update() {
    m_winmanager->Update();
    for(unsigned int i = 0; i < m_winmanager->GetWindowCount(); ++i) {
        Window *w = m_winmanager->Get(i);
        if(w->m_y < 21) {
            w->SetPosition(w->m_x, 21);
        }
    }


    if(m_havelevel) {
        m_level->Update();
    }
    KeyBinds();
}

void Editor::Draw() {
    if(m_havelevel) {
        m_level->Draw();
        //m_texturemanager->Get(0)->DrawTile(0, 0, 0);
    }
    m_winmanager->Draw();
}


void Editor::KeyBinds() {
    if(m_havelevel) {
        //Switch tool
        if(m_level->m_ispainting == false) {    //can't switch while the tool is being used
            if(IsKeyPressed(KEY_ONE)) {
                m_level->m_selectedtool = 0;    //pen
            }
            if(IsKeyPressed(KEY_TWO)) {
                m_level->m_selectedtool = 1;    //rectangle
            }
        }
    }

    //Open windows
    if(IsKeyDown(KEY_LEFT_ALT)) {
        if(IsKeyPressed(KEY_W) && m_havelevel) {   //ZOOM
            Window* winptr = m_winmanager->FindWithID(WINID_ZOOM);
            if(winptr == NULL) {
                m_winmanager->Add(new ZoomWindow(this));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_T) && m_havelevel) {   //TEXTURE LIST
            Window* winptr = m_winmanager->FindWithID(WINID_TEXTURELIST);
            if(winptr == NULL) {
                m_winmanager->Add(new TextureListWindow(this));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_L) && m_havelevel) {   //LAYER LIST
            Window* winptr = m_winmanager->FindWithID(WINID_LAYERLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new LayerListWindow(m_level));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_P) && m_havelevel) {   //PALETTE
            Window* winptr = m_winmanager->FindWithID(WINID_PALETTE);
            if(winptr == NULL) {
                m_winmanager->Add(new PaletteWindow(this));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_O) && m_havelevel) {                   //OBJECT LIST WINDOW
            Window* winptr = m_winmanager->FindWithID(WINID_OBJECTLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new ObjectListWindow(this));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

    }
    else if(IsKeyDown(KEY_LEFT_CONTROL)) {
        if(IsKeyPressed(KEY_KP_0) && m_havelevel) {
            m_level->m_x = 10;
            m_level->m_y = 10;
        }

        if(g_mouse->m_havebeenused == false) {
            int wheelmovement = (int)GetMouseWheelMove();
            if(wheelmovement != 0) {
                Zoom(wheelmovement, g_mouse->m_x, g_mouse->m_y);
            }
        }

        if(IsKeyPressed(KEY_S) && m_havelevel) {
            Window* winptr = m_winmanager->FindWithID(WINID_SAVELEVEL);
            if(winptr == NULL) {
                m_winmanager->Add(new SaveWindow(this));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }
    }
    else {
        if(IsKeyPressed(KEY_G) && m_havelevel) {
            m_level->m_showgrid = !m_level->m_showgrid;
        }

        if(IsKeyPressed(KEY_N) && m_havelevel) {
            m_level->m_shownumbers = !m_level->m_shownumbers;
        }
    }
}

void Editor::Zoom(int relativezoom, int zoomxcenter, int zoomycenter) {
    if(m_havelevel == false) {
        return;
    }
    
    if(m_level->m_zoom + relativezoom < 1) {  //TODO : handle this correctly
        return;
    }

    //calculate distance between zoom center and grid's top left
    float distancex = (float)(m_level->m_x - zoomxcenter);
    float distancey = (float)(m_level->m_y - zoomycenter);

    //"cancel" old zoom and apply new zoom
    float currentzoom = (float) m_level->m_zoom;
    distancex = (distancex / currentzoom) * (currentzoom+(float)relativezoom);
    distancey = (distancey / currentzoom) * (currentzoom+(float)relativezoom);

    //apply new position
    m_level->m_x = zoomxcenter + (int)distancex;
    m_level->m_y = zoomycenter + (int)distancey;

    //apply new zoom to grid
    m_level->m_zoom += relativezoom;
}

void Editor::CreateNewLevel(int width, int height, int boxwidth, int boxheight) { 
    if(m_havelevel) {
        delete m_level;
        //Do this to avoid problem if the newly created level have different tile sizes.
        delete m_texturemanager;
        m_texturemanager = new TextureManager(this);
    }

    m_level = new Level(width, height, boxwidth, boxheight);
    printf("Allocated level at %p, layer count : %i\n", m_level, m_level->m_layercount);

    while(m_winmanager->GetWindowCount() > 0) {
        m_winmanager->Remove(m_winmanager->Get(0));
    }

    m_havelevel = true;

    m_level->m_editor = this;
    m_level->m_isineditor = true;
}

void Editor::LoadFromFile(const char* filename) {
    Level* newlevel = ParseLVLFile(std::string(filename));    

    if(newlevel != NULL) {
        //Add the new level to the editor
        if(m_havelevel) {
            delete m_level;
        }
        m_havelevel = true;
        m_level = newlevel;

        m_level->m_editor = this;
        m_level->m_isineditor = true;

        m_name = std::string(filename);
    }
}