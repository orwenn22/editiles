#ifndef CPP_STRING_VALUE_H
#define CPP_STRING_VALUE_H

#include "Widget.h"

#include <string>

class CppStringValue : public Widget {
    public:
    CppStringValue(WidgetManager* widgetmanager, int x, int y, std::string* stringptr);

    void Draw() override;

    std::string* m_stringptr;
};

#endif