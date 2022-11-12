#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

#include <string>
#include <raylib.h>

class Button;

typedef void (*ButtonAction) (Button*);

//Button is a Widget on which the user can click.
//it uses the information of g_mouse.
//If the Button is clicked, it can execute a function.
class Button : public Widget {
    public:
    Button(int x, int y, int w, int h);

    void Update() override;
    void Draw() override;

    void SetAction(ButtonAction action);    //change the action of the button
    void SetText(std::string text);         //change the text on the button

    private:    //Maybe other classes need to access these ?
    ButtonAction m_action;  //Action executed when the user click on the button.

    std::string m_text; //text written on the button.
};

#endif