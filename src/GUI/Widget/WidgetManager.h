#ifndef WIDGET_MANAGER_H
#define WIDGET_MANAGER_H

#include <vector>

class Widget;
class Window;

class WidgetManager {
    public:
    WidgetManager(Window* win);
    ~WidgetManager();

    void Update();
    void UpdateAllPos();
    void Draw();

    void Add(Widget* newwidget);
    void Remove(Widget* widgetptr);

    Window* m_window;
    
    std::vector<Widget*> m_widgets;
    unsigned int m_count;
};

#endif