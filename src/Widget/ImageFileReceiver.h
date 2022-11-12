#ifndef IMAGE_FILE_RECEIVER_H
#define IMAGE_FILE_RECEIVER_H

#include "../GUI/Widget/Widget.h"

class ImageFileReceiver : public Widget {
    public:
    ImageFileReceiver(int x, int y, int w, int h);

    void Update() override;
    void Draw() override;
};

#endif