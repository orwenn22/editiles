#ifndef EDITOR_H
#define EDITOR_H

class Application;
class BottomBar;
class Level;
class MouseObject;
class TextureManager;
class WindowCorner;
class WindowManager;

class Editor {
    public:
    Editor();
    Editor(int lvlwidth, int lvlheight, int tilewidth, int tileheight);
    ~Editor();

    void Update();
    void Draw();

    void KeyBinds();

    void Zoom(int relativezoom, int zoomxcenter, int zoomycenter);

    void CreateNewLevel(int width, int height, int boxwidth, int boxheight);

    void LoadFromFile(const char* filename);

    //private:
    Level* m_level;
    TextureManager* m_texturemanager;
    WindowManager* m_winmanager;

    Application* m_app;

    bool m_havelevel;
};

#endif