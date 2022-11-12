#ifndef BOTTOM_BAR_H
#define BOTTOM_BAR_H

#include <string>

class BottomBar {
    public:
    BottomBar();

    void Update();
    void Draw();

    void TextAppend(std::string strtoappend);
    void TextClear();

    int m_y;
    std::string m_text;
};

#endif