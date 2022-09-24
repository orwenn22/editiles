#ifndef LAYER_LIST_H
#define LAYER_LIST_H

#include "../GUI/Widget/ElementList.h"

class LayerList : public ElementList {
    public:
    LayerList(WidgetManager* widgetmanager, int x, int y, int w, int h);

    void RightClickOn(int clickindex) override;
    void LeftClickOn(int clickindex) override;

    void LeftReleaseOn(int releaseindex) override;

    void DrawElement(int painterx, int paintery, int elementindex) override;

    int GetElementCount() override;

    int GetSelectedElement() override;
    void SetSelectedElement(int newselection) override;
};

#endif