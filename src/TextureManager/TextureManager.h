#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <vector>

class Editor;
class TextureObject;

class TextureManager {
    public:
    TextureManager(Editor* editor);
    ~TextureManager();

    void Add(TextureObject* newtxtr);
    void Remove(TextureObject* txtrptr);
    TextureObject* Get(int index);
    int GetIndex(TextureObject* txtrobj);

    Editor* m_parrent;

    std::vector<TextureObject*> m_textures;
    int m_texturecount;
};

#endif