#include "TextureInfoWindow.h"

#include "../../Editor.h"
#include "../../Layer/Layer.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/Label.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../../Level.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../ObjectManager/ObjectTemplate.h"
#include "../../TextureManager/TextureManager.h"
#include "../../TextureManager/TextureObject.h"
#include "../../Widget/TexturePreview.h"
#include "../WinIDs.h"


void DeleteTextureButton(Button* but) {
    TextureInfoWindow* win = ((TextureInfoWindow*)(but->m_parrent->m_window));
    TextureObject* textureobject = win->m_textureobjectptr;
    Editor* editor = win->m_editor;

    //check if texture is used by layers
    for(int i = 0; i < editor->m_level->m_layercount; i++) {
        Layer* layer = editor->m_level->GetLayer(i);
        if(layer->m_havetexture && layer->m_textureobj == textureobject) {
            layer->m_havetexture = false;
            layer->m_textureobj = NULL;
        }
    }

    //check if texture is used by object templates
    for(int i = 0; i < editor->m_level->m_objectmanager->GetObjectTemplateCount(); i++) {
        ObjectTemplate* object = editor->m_level->m_objectmanager->Get(i);
        if(object->m_havetexture && object->m_textureobj == textureobject) {
            object->m_havetexture = false;
            object->m_textureobj = NULL;
        }
    }

    //printf("%p\n", textureobject);
    editor->m_texturemanager->Remove(textureobject);
    win->m_parrent->Remove(win);
}

TextureInfoWindow::TextureInfoWindow(TextureObject* textureobjectptr, Editor* editor) : Window() {
    m_editor = editor;

    m_id = WINID_TEXTUREINFO;
    SetPosition(100, 100);
    
    m_width = 150;
    m_height = 200;

    m_titlebarcolor = RED;

    m_textureobjectptr = textureobjectptr;

    m_titlebartext = TextFormat("Texture %p", textureobjectptr);

    m_widgetmanager->Add(new Label(5, 18, "Name :"));
    m_widgetmanager->Add(new CppStringField(40, 15, 107, &(m_textureobjectptr->m_name)));

    Button* deletebutton = new Button(5, 32, 50, 15);
    deletebutton->SetText("Delete");
    deletebutton->SetAction(DeleteTextureButton);
    m_widgetmanager->Add(deletebutton);


    m_widgetmanager->Add(new TexturePreview(5, 50, 140, 130, m_textureobjectptr));

}