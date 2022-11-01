#ifndef CPP_STRING_FIELD_H
#define CPP_STRING_FIELD_H

#include "Widget.h"

#include <string>

//CppStringField is a widget where the user can input a string
//and it will update a value stored at the destination of a pointer.
//The value stored at the pointer change as soon as the user type something.
class CppStringField : public Widget {
    public:
    CppStringField(WidgetManager* wm, int x, int y, int w, std::string* variableptr);

    void Update() override;
    void Draw() override;

    std::string* m_variableptr; //Pointer to the value that the CppStringField Change.

    private:
    bool m_isselected;          //If set to true, the CppStrihgField will read the imput from the keyboard and update the string stored at the pointer.

    bool m_allowspace;          //is set to true, it is possible to input a space character
};

#endif