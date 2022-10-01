#include "TextureInfoWindow.h"

#include "../../Editor.h"
#include "../../Layer/Layer.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/Label.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../TextureManager/TextureManager.h"
#include "../../TextureManager/TextureObject.h"
#include "../../Widget/TexturePreview.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void DeleteTextureButton(Button* but) {
    TextureInfoWindow* win = ((TextureInfoWindow*)(but->m_parrent->m_window));
    TextureObject* textureobject = win->m_textureobjectptr;

    //check if texture is used by layer
    for(int i = 0; i < g_editor->m_level->m_layercount; i++) {
        Layer* layer = g_editor->m_level->GetLayer(i);
        if(layer->m_havetexture && layer->m_textureobj == textureobject) {
            layer->m_havetexture = false;
            layer->m_textureobj = NULL;
            break;
        }
    }

    //printf("%p\n", textureobject);
    g_editor->m_texturemanager->Remove(textureobject);
    g_editor->m_winmanager->Remove(win);
}

TextureInfoWindow::TextureInfoWindow(WindowManager* winmanager, TextureObject* textureobjectptr) : Window(winmanager) {
    m_id = WINID_TEXTUREINFO;
    SetPosition(100, 100);
    
    m_width = 150;
    m_height = 200;

    m_titlebarcolor = RED;

    m_textureobjectptr = textureobjectptr;

    m_titlebartext = TextFormat("Texture %p", textureobjectptr);

    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 18, "Name :"));
    m_widgetmanager->Add(new CppStringField(m_widgetmanager , 40, 15, 107, &(m_textureobjectptr->m_name)));

    Button* deletebutton = new Button(m_widgetmanager, 5, 32, 50, 15);
    deletebutton->SetText("Delete");
    deletebutton->SetAction(DeleteTextureButton);
    m_widgetmanager->Add(deletebutton);


    m_widgetmanager->Add(new TexturePreview(m_widgetmanager, 5, 50, 140, 130, m_textureobjectptr));

}