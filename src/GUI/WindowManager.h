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
    Window* Get(int index);

    void BringOnTop(Window* windowptr);

    Window* FindWithID(int id);

    std::vector<Window*> m_windows;
    unsigned int m_wincount;
};

#endif