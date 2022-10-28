#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <vector>

class Window;

class WindowManager {
    public:
    WindowManager();
    ~WindowManager();

    void Update();
    void Draw();

    void Add(Window* newwindow);
    void Remove(Window* windowptr);

    //Previously : Window* Get(int index);
    Window* Get(unsigned int index);

    void BringOnTop(Window* windowptr);

    Window* FindWithID(int id);

    std::vector<Window*> m_windows;     //contain the pointers to all the Windows in the WindowManager
    unsigned int m_wincount;            //number of windows in the WindowManager
};

#endif