#ifndef EDITOR_H
#define EDITOR_H

class Level;
class MouseObject;
class TextureManager;
class WindowManager;

class Editor {
    public:
    Editor();
    ~Editor();

    void Update();
    void Draw();

    void KeyBinds();

    void CreateNewLevel(int width, int height, int boxwidth, int boxheight);

    //private:
    Level* m_level;
    MouseObject* m_mouse;
    TextureManager* m_texturemanager;
    WindowManager* m_winmanager;

    bool m_havelevel;
};

#endif