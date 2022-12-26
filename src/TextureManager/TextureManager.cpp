#include "TextureManager.h"

#include "TextureObject.h"

TextureManager::TextureManager(Editor* editor) {
    m_parrent = editor;
    m_texturecount = 0;
}

TextureManager::~TextureManager() {
    for(int i = 0; i < m_texturecount; i++) {
        delete m_textures[i];
    }
}


void TextureManager::Add(TextureObject* newtextr) {
    m_textures.push_back(newtextr);
    m_texturecount++;
}

void TextureManager::Remove(TextureObject* txtrptr) {
    for(int i = 0; i < m_texturecount; i++) {
        if(m_textures[i] == txtrptr) {
            delete txtrptr;
            m_textures.erase(m_textures.begin() + i);
            m_texturecount--;
            return;
        }
    }
}

TextureObject* TextureManager::Get(int index) {
    if(index >= 0 && index < m_texturecount) {
        return m_textures[index];
    }
    return NULL;
}

int TextureManager::GetIndex(TextureObject* txtrobj) {
    for(int i = 0; i < m_texturecount; i++) {
        if(m_textures[i] == txtrobj) return i;
    }
    return -1;
}