#ifndef TEXTURE_PREVIEW_WINDOW_H
#define TEXTURE_PREVIEW_WINDOW_H

#include "../GUI/Window.h"

class TextureObject;

class TexturePreviewWindow : public Window {
    public:
    TexturePreviewWindow(WindowManager* winmanager, TextureObject* txtrobj);
};

#endif