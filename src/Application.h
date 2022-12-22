#ifndef APPLICATION_H
#define APPLICATION_H

class BottomBar;
class Editor;
class MouseObject;
class WindowCorner;
class WindowManager;

class Application {
    public:
    Application();
    ~Application();

    void Update();
    void Draw();

    void AddEditor(Editor* editor);

    MouseObject* m_mouse;
    BottomBar* m_bottombar;
    WindowCorner* m_corner;
    WindowManager* m_winmanager;

    Editor* m_editor;
};

#endif