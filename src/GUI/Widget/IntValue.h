#ifndef INT_VALUE_H
#define INT_VALUE_H

#include "Widget.h"

//IntValue is a widget that can draw a int value using a pointer to this value.
//When the value stored at the destination of the pointer is changed, the widget
//will also update. (well, technicly, we just draw the widget every frame ( ͡° ͜ʖ ͡°) )
class IntValue : public Widget {
    public:
    IntValue(WidgetManager* widgetmanager, int x, int y, int* value);

    void Draw() override;

    int* m_value;   //Pointer to the value, specified in the constructor
};

#endif