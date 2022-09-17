#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

#include <string>
#include <raylib.h>

class Button;

typedef void (*ButtonAction) (Button*);

class Button : public Widget {
    public:
    Button(WidgetManager* wm, int x, int y, int w, int h);

    void Update() override;
    void Draw() override;

    void SetAction(ButtonAction action);
    void SetText(std::string text);

    ButtonAction m_action;

    std::string m_text;
};

#endif