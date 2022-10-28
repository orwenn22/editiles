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

    //Add a Window to the WindowManager
    void Add(Window* newwindow);

    //Remove a Window using its pointer. Will deallocate the window.
    void Remove(Window* windowptr);

    //Previously : Window* Get(int index);
    //Get a pointer to a window using the index.
    //Return NULL if there is no window corresponding to the index.
    Window* Get(unsigned int index);

    //Will put the windowptr at index 1 of m_windows
    void BringOnTop(Window* windowptr);

    Window* FindWithID(int id);

    std::vector<Window*> m_windows;     //contain the pointers to all the Windows in the WindowManager
    unsigned int m_wincount;            //number of windows in the WindowManager
};

#endif