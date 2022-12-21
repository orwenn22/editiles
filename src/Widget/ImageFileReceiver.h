#ifndef IMAGE_FILE_RECEIVER_H
#define IMAGE_FILE_RECEIVER_H

#include "../GUI/Widget/Widget.h"

class Editor;

class ImageFileReceiver : public Widget {
    public:
    ImageFileReceiver(int x, int y, int w, int h, Editor* editor);

    void Update() override;
    void Draw() override;

    Editor* m_editor;
};

#endif