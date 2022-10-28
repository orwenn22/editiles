#ifndef CPP_STRING_VALUE_H
#define CPP_STRING_VALUE_H

#include "Widget.h"

#include <string>

//CppStringValue is a Widget that can display a std::string using its pointer.
//If the string stored at the pointer change, the widget also update.
//(this is basicly a rip-off of IntValue but for a std::string)
class CppStringValue : public Widget {
    public:
    CppStringValue(WidgetManager* widgetmanager, int x, int y, std::string* stringptr);

    void Draw() override;

    std::string* m_stringptr;   //Pointer to the string.
};

#endif