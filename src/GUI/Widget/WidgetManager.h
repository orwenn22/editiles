#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <vector>

class Widget;
class Window;

class WidgetManager {
    public:
    WidgetManager();
    WidgetManager(Window* win);
    ~WidgetManager();

    void Update();                      //Call Widget::Update() on all widgets in m_widgets
    void ChangeBasePos(int x, int y);   //change the base position of the widget manager. Will call UpdateAllPos().
    void UpdateAllPos();                //recalculate all the absolute position of the widgets in m_widgets.
    void Draw();                        //draw all the widgets in m_widgets.

    void Add(Widget* newwidget);        //Add a widget with its pointer.
    void Remove(Widget* widgetptr);     //Remove a widget with its pointer.

    //x and y position of the WidgetManager
    //these value are used to calculate the
    //absolute position of the widgets in m_widgets
    //when UpdateAllPos() is called
    int m_baseposx;
    int m_baseposy;

    Window* m_window;           //Will store the pointer the pointer of the parrent Window if the WidgetManager is part of a Window.
    bool m_isinwindow;          //true if the WidgetManager is part of a Window.

    std::vector<Widget*> m_widgets;     //contain all of the Widgets in the WidgetManager.
    unsigned int m_count;               //number of widgets in m_widget.
};

#endif