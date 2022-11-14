#ifndef BORDERLESS_WINDOW_H
#define BORDERLESS_WINDOW_H

#include "Window.h"

class BorderlessWindow : public Window {
    public:
    BorderlessWindow();
    virtual ~BorderlessWindow();

    bool PreUpdate() override;
    void Draw() override;
};

#endif