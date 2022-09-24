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

    virtual int GetSelectedElement();                   //return the selected element, needs to be overrided.
    virtual void SetSelectedElement(int newselection);  //set the selected element, needs to be overrided.

    virtual void PreInputCheck();   //called when mouse is over the widget. Override to add custom behavior to widget.

    int m_firstelementindex;
    int m_elementheight;
    bool m_canselectelement;
};

#endif