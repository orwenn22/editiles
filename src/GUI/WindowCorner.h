#ifndef WINDOW_CORNER_H
#define WINDOW_CORNER_H

class WindowCorner {
    public:
    WindowCorner(int minwidth, int minheight);

    void Update();
    void Draw();

    int m_minwidth;
    int m_minheight;

    int m_x;
    int m_y;

    int m_mouseoffsetx;
    int m_mouseoffsety;

    bool m_followmouse;
};

#endif