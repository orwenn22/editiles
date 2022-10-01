#ifndef INT_VALUE_H
#define INT_VALUE_H

#include "Widget.h"

class IntValue : public Widget {
    public:
    IntValue(WidgetManager* widgetmanager, int x, int y, int* value);

    void Draw() override;

    int* m_value;
};

#endif