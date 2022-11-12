#ifndef TEXTURE_INFO_WINDOW_H
#define TEXTURE_INFO_WINDOW_H

#include "../../GUI/Window.h"

class TextureObject;

class  TextureInfoWindow : public Window {
    public:
    TextureInfoWindow(TextureObject* textureobjectptr);


    TextureObject* m_textureobjectptr;
};

#endif