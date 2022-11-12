#ifndef WIDGET_H
#define WIDGET_H

class Editor;
class WidgetManager;

class Widget {
    public:
    Widget(int x, int y, int w, int h);
    virtual ~Widget();

    //Called by WidgetManager::Update()
    //override to add custom behavior.
    virtual void Update();

    //Recalculate m_x and m_y with m_parrent's base position and the offset from m_parrent's base position.
    //Normally called by WidgetManager::UpdateAllPos()
    //Calling this if m_parrent is undefined will cause a crash
    void UpdatePos();

    //Called by WidgetManager::Draw()
    //Draw the widget at position m_x and m_y.
    //override to specify how the widget should be drawed.
    virtual void Draw();

    //Change the values of m_xoffset and m_yoffset.
    //Will also call UpdatePos()
    void SetPos(int x, int y);

    //contain a pointer to the parrent WidgetManager. Can also be used to access the parrent Window (m_parrent->m_window).
    //Given by WidgetManager::Add()
    WidgetManager* m_parrent;

    //offset from the parrent WidgetManager's base position (relative position)
    //the x and y parameters from the constructor set these two valuess
    int m_xoffset;
    int m_yoffset;

    //size of the widget, specified with the constructor.
    int m_width;
    int m_height;

    //Real (absolute) position of the widget on screen.
    int m_x;
    int m_y;
};

#endif