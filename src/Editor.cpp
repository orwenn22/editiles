#include "Editor.h"

#include "FileUtil/FileUtil.h"
#include "GUI/BottomBar.h"
#include "GUI/Mouse/MouseObject.h"
#include "GUI/WindowCorner.h"
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
#include "Windows/NewLevelWindow.h"
#include "Windows/Object/ObjectListWindow.h"
#include "Windows/PaletteWindow.h"
#include "Windows/Texture/TextureListWindow.h"
#include "Windows/WinIDs.h"
#include "Windows/ZoomWindow.h"
#include "Zoom.h"

#include "ParseFunctions.h"

#include <raylib.h>

Editor::Editor() {
    m_havelevel = false;
    //m_havelevel = true;
    //m_level = new Level(this);
    m_mouse = InitMouseGlobal();

    m_texturemanager = new TextureManager(this);

    m_winmanager = new WindowManager();
    //m_winmanager->Add(new Window(m_winmanager));

    m_bottombar = new BottomBar();
    m_corner = new WindowCorner(500, 500);
}

Editor::~Editor() {
    if(m_havelevel) {
        delete m_level;
    }
    delete m_texturemanager;
    delete m_winmanager;
    delete m_mouse;

    delete m_corner;
}

void Editor::Update() {
    m_mouse->Update();
    m_corner->Update();
    m_bottombar->Update();
    m_winmanager->Update();
    if(m_havelevel) {
        m_level->Update();
    }
    KeyBinds();

    m_mouse->PostUpdate();
}

void Editor::Draw() {
    if(m_havelevel) {
        m_level->Draw();
        //m_texturemanager->Get(0)->DrawTile(0, 0, 0);
    }
    m_winmanager->Draw();
    m_bottombar->Draw();
    m_corner->Draw();
    m_mouse->Draw();
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
                m_winmanager->Add(new ZoomWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_T) && m_havelevel) {   //TEXTURE LIST
            Window* winptr = m_winmanager->FindWithID(WINID_TEXTURELIST);
            if(winptr == NULL) {
                m_winmanager->Add(new TextureListWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_L) && m_havelevel) {   //LAYER LIST
            Window* winptr = m_winmanager->FindWithID(WINID_LAYERLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new LayerListWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_P) && m_havelevel) {   //PALETTE
            Window* winptr = m_winmanager->FindWithID(WINID_PALETTE);
            if(winptr == NULL) {
                m_winmanager->Add(new PaletteWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_O) && m_havelevel) {                   //OBJECT LIST WINDOW
            Window* winptr = m_winmanager->FindWithID(WINID_OBJECTLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new ObjectListWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_N)) {                   //NEW LEVEL WINDOW
            Window* winptr = m_winmanager->FindWithID(WINID_NEWLEVEL);
            if(winptr == NULL) {
                m_winmanager->Add(new NewLevelWindow());
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

    }

    if(IsKeyPressed(KEY_KP_0) && m_havelevel) {
        m_level->m_x = 10;
        m_level->m_y = 10;
    }

    if(IsKeyDown(KEY_LEFT_CONTROL) && m_mouse->m_havebeenused == false) {
        int wheelmovement = (int)GetMouseWheelMove();
        if(wheelmovement != 0) {
            Zoom(wheelmovement, m_mouse->m_x, m_mouse->m_y);
        }
    }

    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S) && m_havelevel) {
        m_level->Save("out.lvl");
        printf("Level saved !\n");
    }
}


void Editor::CreateNewLevel(int width, int height, int boxwidth, int boxheight) { 
    if(m_havelevel) {
        delete m_level;
    }

    m_level = new Level(width, height, boxwidth, boxheight);
    printf("Allocated level at %p, layer count : %i\n", m_level, m_level->m_layercount);

    while(m_winmanager->m_wincount > 0) {
        m_winmanager->Remove(m_winmanager->Get(0));
    }

    m_havelevel = true;
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
    }
}