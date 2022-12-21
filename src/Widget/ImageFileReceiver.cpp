#include "ImageFileReceiver.h"

#include "../Editor.h"
#include "../GUI/Mouse/MouseObject.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/WindowManager.h"
#include "../Level.h"
#include "../TextureManager/TextureManager.h"
#include "../TextureManager/TextureObject.h"

#include <raylib.h>

ImageFileReceiver::ImageFileReceiver(int x, int y, int w, int h, Editor* editor) : Widget(x, y, w, h) {
    m_editor = editor;
}

void ImageFileReceiver::Update() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {
            if(g_mouse->m_havefiles) {
                if(g_mouse->m_fileslist.count == 1) {
                    TextureObject* newtxtrobj =  new TextureObject(g_mouse->m_fileslist.paths[0], "Imported Texture", m_editor->m_level->m_boxwidth, m_editor->m_level->m_boxheight);
                    if(newtxtrobj->m_texture.id <= 0) {     //loading failure
                        delete newtxtrobj;
                    } else {    //success
                        m_editor->m_texturemanager->Add(newtxtrobj);
                        m_editor->m_winmanager->Remove(m_parrent->m_window);
                    }
                }
            }
        }
    }
}

void ImageFileReceiver::Draw() {
    DrawLine(m_x, m_y, m_x+20, m_y, WHITE);
    DrawLine(m_x, m_y, m_x, m_y+20, WHITE);

    DrawLine(m_x+m_width, m_y, m_x+m_width-20, m_y, WHITE);
    DrawLine(m_x+m_width, m_y, m_x+m_width, m_y+20, WHITE);

    DrawLine(m_x, m_y+m_height, m_x+20, m_y+m_height, WHITE);
    DrawLine(m_x, m_y+m_height, m_x, m_y+m_height-20, WHITE);

    DrawLine(m_x+m_width, m_y+m_height, m_x+m_width-20, m_y+m_height, WHITE);
    DrawLine(m_x+m_width, m_y+m_height, m_x+m_width, m_y-20+m_height, WHITE);

    DrawText("Drag & Drop", m_x, m_y + m_width/2 - 10, 10, WHITE);
    DrawText("a file here", m_x, m_y + m_width/2 + 10, 10, WHITE);
}