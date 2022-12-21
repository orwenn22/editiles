#ifndef TEXTURE_LIST_H
#define TEXTURE_LIST_H

#include "../GUI/Widget/ElementList.h"

class Editor;

class TextureList : public ElementList {
    public:
    TextureList(int x, int y, int w, int h, Editor* editor);


    void RightClickOn(int clickindex) override;
    void LeftClickOn(int clickindex) override;

    void DrawElement(int painterx, int paintery, int elementindex) override;

    int GetElementCount() override;

    void PreInputCheck() override;


    Editor* m_editor;
};

#endif