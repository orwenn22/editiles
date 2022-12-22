#ifndef TEXTURE_INFO_WINDOW_H
#define TEXTURE_INFO_WINDOW_H

#include "../../GUI/Window.h"

class Editor;
class TextureObject;

//Opened from TextureList
class  TextureInfoWindow : public Window {
    public:
    TextureInfoWindow(TextureObject* textureobjectptr, Editor* editor);


    TextureObject* m_textureobjectptr;
    Editor* m_editor;
};

#endif