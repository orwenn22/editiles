#ifndef ELEMENT_LIST_H
#define ELEMENT_LIST_H

#include "Widget.h"

class ElementList : public Widget {
    public:
    ElementList(WidgetManager* widgetmanager, int x, int y, int w, int h);

    void Update() override;
    void Draw() override;

    virtual void RightClickOn(int clickindex);      //called when an element in the list is right clicked
    virtual void LeftClickOn(int clickindex);       //called when an element in the list is left clicked
    virtual void RightReleaseOn(int releaseindex);    //called when an element in the list is right released
    virtual void LeftReleaseOn(int releaseindex);     //called when an element in the list is left released

    virtual void DrawElement(int painterx, int paintery, int elementindex);   //called when drawing an element of the list

    virtual int GetElementCount();

    virtual int GetSelectedElement();
    virtual void SetSelectedElement(int newselection);

    int m_firstelementindex;
    int m_elementheight;
    bool m_canselectelement;
};

#endif