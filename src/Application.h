#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <vector>

class BottomBar;
class Editor;
class MouseObject;
class WindowCorner;
class WindowManager;

class TabBar;
class EditorTabsHandler;

class Application {
    public:
    Application();
    ~Application();

    void Update();
    void UpdateEditor();

    void Draw();
    void DrawEditor();

    void AddEditor(Editor* editor);
    void RemoveEditor(int index);
    std::string GetEditorName(int index);
    void LoadFile(std::string filename);


    void KeyBindsUpdate();
    void OpenNewLevelWindow();

    MouseObject* m_mouse;
    BottomBar* m_bottombar;
    WindowCorner* m_corner;
    WindowManager* m_winmanager;

    TabBar* m_tabbar;
    EditorTabsHandler* m_tabshandler;

    std::vector<Editor*> m_editors;
    int m_editorcount;
    int m_currenteditor;
};

#endif