#include "Editor.h"

#include "GUI/Window.h"
#include "GUI/WindowManager.h"
#include "Level.h"
#include "Mouse/MouseObject.h"
#include "TextureManager/TextureManager.h"
#include "TextureManager/TextureObject.h"
#include "Windows/LayerListWindow.h"
#include "Windows/NewLevelWindow.h"
#include "Windows/PaletteWindow.h"
#include "Windows/TextureListWindow.h"
#include "Windows/WinIDs.h"
#include "Windows/ZoomWindow.h"
#include "Zoom.h"

#include <raylib.h>

Editor::Editor() {
    m_havelevel = false;
    //m_havelevel = true;
    //m_level = new Level(this);
    m_mouse = new MouseObject();

    m_texturemanager = new TextureManager(this);

    m_winmanager = new WindowManager();
    m_winmanager->Add(new Window(m_winmanager));
}

Editor::~Editor() {
    if(m_havelevel) {
        delete m_level;
    }
    delete m_texturemanager;
    delete m_winmanager;
    delete m_mouse;
}

void Editor::Update() {
    m_mouse->Update();
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
    m_mouse->Draw();
}


void Editor::KeyBinds() {
    if(IsKeyDown(KEY_LEFT_ALT)) {
        if(IsKeyPressed(KEY_W) && m_havelevel) {   //ZOOM
            Window* winptr = m_winmanager->FindWithID(WINID_ZOOM);
            if(winptr == NULL) {
                m_winmanager->Add(new ZoomWindow(m_winmanager));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_T) && m_havelevel) {   //TEXTURE LIST
            Window* winptr = m_winmanager->FindWithID(WINID_TEXTURELIST);
            if(winptr == NULL) {
                m_winmanager->Add(new TextureListWindow(m_winmanager));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_L) && m_havelevel) {   //LAYER LIST
            Window* winptr = m_winmanager->FindWithID(WINID_LAYERLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new LayerListWindow(m_winmanager));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_P) && m_havelevel) {   //PALETTE
            Window* winptr = m_winmanager->FindWithID(WINID_PALETTE);
            if(winptr == NULL) {
                m_winmanager->Add(new PaletteWindow(m_winmanager));
            }
            else {
                m_winmanager->BringOnTop(winptr);
            }
        }

        if(IsKeyPressed(KEY_N)) {                   //NEW LEVEL WINDOW
            Window* winptr = m_winmanager->FindWithID(WINID_NEWLEVEL);
            if(winptr == NULL) {
                m_winmanager->Add(new NewLevelWindow(m_winmanager));
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
        Zoom((int)GetMouseWheelMove(), m_mouse->m_x, m_mouse->m_y);
    }
}


void Editor::CreateNewLevel(int width, int height, int boxwidth, int boxheight) { 
    if(m_havelevel) {
        delete m_level;
    }

    m_level = new Level(width, height, boxwidth, boxheight);
    printf("Allocated level at %p, layer count : %i\n", m_level, m_level->m_layercount);

    m_havelevel = true;
}