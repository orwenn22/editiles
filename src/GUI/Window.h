#ifndef WINDOW_H
#define WINDOW_H

#include <raylib.h>

#include <string>

class WidgetManager;
class WindowManager;

class Window {
    public:
    Window();

    //Called by WindowManager::~WindowManager()
    virtual ~Window();

    //Called by WindowManager::Update().
    //It will call PreUpdate(), Update() and PostUpdate()
    //If the window is destroyed durring PreUpdate(), the 2 other methods won't be executed
    void MUpdate();

    //Called by MUpdate()
    //Will Update the window's postion, check if it is closed and check if it is off-screen.
    //if this return true, the Update, PostUpdate and Draw mathods won't be executed.
    virtual bool PreUpdate();
    //Called by MUpdate()
    //Will update all the widgets in m_widgetmanager.
    void Update();
    //Called by MUpdate()
    //Check if the f_mouse is overring the window.
    //Is so, set its m_havebeenused to true so windows bellow the current one
    //don't interact with it.
    void PostUpdate();

    //Called by WindowManager::Draw()
    //Will draw window border, title bar and all the widgets of m_widgetmanager.
    virtual void Draw();

    //Set the x and y position of the window (top left corner).
    void SetPosition(int x, int y);

    WidgetManager* m_widgetmanager;     //Pointer to the WidgetManager of the window. Contains all the Widgets of the window.
    WindowManager* m_parrent;           //Pointer to the WindowManager the window is in. Given by WindowManager::Add().

    int m_x;
    int m_y;

    int m_width;    //width of the window
    int m_height;   //height of the window

    //when dragging window
    bool m_followmouse;     //if set to true, the windoww will follow the mouse.
    int m_xmouseoffset;     //calculated when the title bar is clicked in order to properly follow the mouse.
    int m_ymouseoffset;     //^^^

    std::string m_titlebartext;     //Color of the titlebar of the window.
    Color m_titlebartextcolor;      //Text of the title bar of the window
    
    Color m_titlebarcolor;          //Color of the text of the title bar of the window.

    int m_id;   //Optional value corresponding to the type of the window.
};

#endif