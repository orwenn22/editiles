#ifndef EDITOR_H
#define EDITOR_H

class Level;
class MouseObject;
class TextureManager;
class WindowCorner;
class WindowManager;

class Editor {
    public:
    Editor();
    ~Editor();

    void Update();
    void Draw();

    void KeyBinds();

    void CreateNewLevel(int width, int height, int boxwidth, int boxheight);

    void LoadFromFile(const char* filename);

    //private:
    Level* m_level;
    MouseObject* m_mouse;
    TextureManager* m_texturemanager;
    WindowManager* m_winmanager;

    WindowCorner* m_corner;

    bool m_havelevel;
};

#endif