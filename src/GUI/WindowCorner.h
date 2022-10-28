#ifndef WINDOW_CORNER_H
#define WINDOW_CORNER_H

class WindowCorner {
    public:
    WindowCorner(int minwidth, int minheight);

    void Update();
    void Draw();

    //other classes might not need to access these properties (?)
    private:
    int m_minwidth;     //minimum window width that the coner will allow resizing to.
    int m_minheight;    //minimum window height that the coner will allow resizing to.

    int m_x;        //X position of the top left of the corner
    int m_y;        //Y position of the top right of the corner

    int m_mouseoffsetx;     //mouse offset calculated when the corner is clicked
    int m_mouseoffsety;

    bool m_followmouse;     //if set to true, the corner will follow the mouse and resize the window.
};

#endif