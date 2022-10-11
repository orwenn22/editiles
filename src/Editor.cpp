#include "Editor.h"

#include "FileUtil/FileUtil.h"
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

#include <raylib.h>

Editor::Editor() {
    m_havelevel = false;
    //m_havelevel = true;
    //m_level = new Level(this);
    m_mouse = InitMouseGlobal();

    m_texturemanager = new TextureManager(this);

    m_winmanager = new WindowManager();
    //m_winmanager->Add(new Window(m_winmanager));

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
    m_corner->Draw();
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

        if(IsKeyPressed(KEY_O) && m_havelevel) {                   //OBJECT LIST WINDOW
            Window* winptr = m_winmanager->FindWithID(WINID_OBJECTLIST);
            if(winptr == NULL) {
                m_winmanager->Add(new ObjectListWindow(m_winmanager));
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

//TODO : better system for loading file ?
void Editor::LoadFromFile(const char* filename) {
    FILE* infile = fopen(filename, "r");

    //check for signature
    if(!(getc(infile) == 'L' && getc(infile) == 'V' && getc(infile) == 'L')) {
        fclose(infile);
        return;
    }


    ///////////////////////////////
    //size infos

    unsigned short lvlwidth = ReadShort(infile);
    unsigned short lvlheight = ReadShort(infile);
    unsigned short boxwidth = ReadShort(infile);
    unsigned short boxheight = ReadShort(infile);

    printf("Creating : %i %i %i %i\n", lvlwidth, lvlheight, boxwidth, boxheight);
    Level* newlevel = new Level(lvlwidth, lvlheight, boxwidth, boxheight);

    //Add the new level to the editor
    if(m_havelevel) {
        delete m_level;
    }
    m_havelevel = true;
    m_level = newlevel;

    /////////////////////////
    //object templates

    unsigned short objecttempcount = ReadShort(infile);
    for(int i = 0; i < objecttempcount; i++) {

        //get name of the object
        std::string objectname = ReadString(infile);

        //create the object template
        ObjectTemplate* objtemplate = new ObjectTemplate(objectname);

        ////////////////////////////////////
        //obj template properties

        unsigned short propcount = ReadShort(infile);
        for(int j = 0; j < propcount; j++) {

            //Get name of the property
            std::string propname = ReadString(infile);

            //create the property
            ObjectProperty* objprop = new ObjectProperty(propname);

            unsigned short proptype = ReadShort(infile);

            //Get the value
            if(proptype == OPT_INT) {       //int
                objprop->SetValue(ReadInt(infile));
            }
            else if(proptype == OPT_STR) {      //str
                std::string propvalue = ReadString(infile);
                objprop->SetValue(propvalue);
            }

            //Add property to object
            if(propname == "x" || propname == "y" || propname == "width" || propname == "height") {     //obligatory property
                //set the value of property
                int propindex = objtemplate->GetPropertyIndex(propname);
                objtemplate->GetProperty(propindex)->SetValue(objprop->defaultvalue.as_int);

                //destroy ppreviously created property
                delete objprop;
            } else {        //custom property
                //Add property to object
                objtemplate->AddProperty(objprop);
            }
        }

        //Add object to level
        newlevel->m_objectmanager->Add(objtemplate);
    }


    ///////////////////////////////////
    //Layers

    unsigned short layercount = ReadShort(infile);
    for(int i = 0; i < layercount; i++) {
        unsigned short layertype = ReadShort(infile);
        std::string layername = ReadString(infile);

        switch (layertype) {
            case LAYERID_GRID:
                {
                    GridLayer* newlayer = new GridLayer(newlevel->m_width, newlevel->m_height, newlevel, layername);
                    newlayer->SetBoxSize(newlevel->m_boxwidth, newlevel->m_boxheight);

                    newlayer->m_tilemapname = ReadString(infile);

                    int boxcount = newlayer->m_width * newlayer->m_height;
                    for(int j = 0; j < boxcount; j++) {
                        newlayer->m_griddata[j] = ReadShort(infile);
                    }

                    newlevel->AddLayer(newlayer);
                }
            break;
            
            case LAYERID_INSTANCE:
                {
                    InstanceLayer* newlayer = new InstanceLayer(newlevel, layername);
                    
                    int instancecount = ReadInt(infile);
                    for(int j = 0; j < instancecount; j++) {
                        //get the object that correspond to the instance
                        int objecttemplateindex = ReadShort(infile);
                        ObjectTemplate* objecttemplate = newlevel->m_objectmanager->Get(objecttemplateindex);

                        //create the instance
                        Instance* newinstance = new Instance(objecttemplate, newlayer, 0, 0);

                        //get all the properties of the instance
                        for(int k = 0; k < objecttemplate->m_propertycount; k++) {
                            int proptype = objecttemplate->GetProperty(k)->type;

                            if(proptype == OPT_INT) {
                                int propvalue = ReadInt(infile);
                                printf("prop value for index %i : %i | ox%x\n", k, propvalue, propvalue);
                                newinstance->m_properties[k].as_int = propvalue;
                            }
                            else if(proptype == OPT_STR) {
                                std::string propvalue = ReadString(infile);
                                
                                int l;
                                for(l = 0; l < propvalue.size(); l++) {
                                    newinstance->m_properties[k].as_str[l] = propvalue[l];
                                }
                                newinstance->m_properties[k].as_str[l] = 0; //null terminator
                            }
                        }

                        //Add instance to layer
                        newlayer->Add(newinstance);
                    }

                    newlevel->AddLayer(newlayer);
                }
            break;

            default:
                printf("Unknown layertype : %i\n", layertype);
            break;
        }
    }


    fclose(infile);
}