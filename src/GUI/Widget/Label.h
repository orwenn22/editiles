#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"

#include <string>
#include <raylib.h>

class Label : public Widget {
    public:
    Label(int x, int y, std::string text);

    void Draw() override;

    void SetText(std::string newtext);
    void SetColor(Color newcolor);

    std::string m_text; //Text of the label.
    Color m_color;      //Color of the text.
};

#endif