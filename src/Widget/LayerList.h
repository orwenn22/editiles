#ifndef LAYER_LIST_H
#define LAYER_LIST_H

#include "../GUI/Widget/ElementList.h"

class Editor;
class Level;

class LayerList : public ElementList {
    public:
    LayerList(int x, int y, int w, int h, Level* level);

    void RightClickOn(int clickindex) override;
    void LeftClickOn(int clickindex) override;

    void LeftReleaseOn(int releaseindex) override;

    void DrawElement(int painterx, int paintery, int elementindex) override;

    int GetElementCount() override;

    int GetSelectedElement() override;
    void SetSelectedElement(int newselection) override;

    void PreInputCheck() override;


    Editor* m_editor;
};

#endif