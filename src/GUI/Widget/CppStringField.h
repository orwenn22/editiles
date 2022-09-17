#ifndef CPP_STRING_FIELD_H
#define CPP_STRING_FIELD_H

#include "Widget.h"

#include <string>

class CppStringField : public Widget {
    public:
    CppStringField(WidgetManager* wm, int x, int y, int w, std::string* variableptr);

    void Update() override;
    void Draw() override;

    std::string* m_variableptr;
    bool m_isselected;
    char m_strtemp[2];
};

#endif