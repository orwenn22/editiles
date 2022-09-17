#ifndef WIDGET_H
#define WIDGET_H

class Editor;
class WidgetManager;

class Widget {
    public:
    Widget(WidgetManager* wm, int x, int y, int w, int h);
    virtual ~Widget();

    virtual void Update();
    void UpdatePos();

    virtual void Draw();

    void SetPos(int x, int y);

    WidgetManager* m_parrent;

    int m_xoffset;  //offset from the window's to left (relative position)
    int m_yoffset;

    int m_width;
    int m_height;

    int m_x;       //Real position on screen
    int m_y;
};

#endif