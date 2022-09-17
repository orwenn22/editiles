#ifndef WINDOW_H
#define WINDOW_H

#include <raylib.h>

#include <string>

class WidgetManager;
class WindowManager;

class Window {
    public:
    Window(WindowManager* winmanager);
    virtual ~Window();

    void MUpdate();     //called by manager
    bool PreUpdate();
    void Update();
    void PostUpdate();

    void Draw();

    void SetPosition(int x, int y);

    WidgetManager* m_widgetmanager;
    WindowManager* m_parrent;

    int m_x;
    int m_y;

    int m_width;
    int m_height;

    //when dragging window
    bool m_followmouse;
    int m_xmouseoffset;
    int m_ymouseoffset;

    std::string m_titlebartext;
    Color m_titlebartextcolor;
    
    Color m_titlebarcolor;

    int m_id;
};

#endif