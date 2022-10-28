#ifndef ELEMENT_LIST_H
#define ELEMENT_LIST_H

#include "Widget.h"

//ElementList is a widget that allow to display a list of several
//elements vertically with a scrollbar.
//When creating a subclass of ElementList, these methods MUST be overrided :
// DrawElement() ; GetElementCount() ; GetSelectedElement ; SetSelectedElement()
class ElementList : public Widget {
    public:
    ElementList(WidgetManager* widgetmanager, int x, int y, int w, int h);

    void Update() override;
    void Draw() override;


    //when overriding these methods, we don't need to care about g_mouse->m_havebeenused
    //because this is allready handled in Update().

    virtual void RightClickOn(int clickindex);      //called when an element in the list is right clicked
    virtual void LeftClickOn(int clickindex);       //called when an element in the list is left clicked
    virtual void RightReleaseOn(int releaseindex);    //called when an element in the list is right released
    virtual void LeftReleaseOn(int releaseindex);     //called when an element in the list is left released

    virtual void DrawElement(int painterx, int paintery, int elementindex);   //called when drawing an element of the list

    virtual int GetElementCount();


    //These two needs to be overrided if m_canselectelement is set to true
    //and the value of index of the selected element is stored somewhere else.
    //If you want this value to be in your subclass, you can add another property to
    //your subclass, and make GetSelectedElement() return this value and make
    //SetSelectedElement() change this value.

    virtual int GetSelectedElement();                   //Return the selected element, needs to be overrided.
    virtual void SetSelectedElement(int newselection);  //Set the selected element, needs to be overrided.

    virtual void PreInputCheck();   //Called when mouse is over the widget. Override to add custom behavior to widget.

    int m_firstelementindex;        //First element that is drawed at the top of the list. Also used to calculate the scrollbar.
    int m_elementheight;            //Height of one element of the list. Used by Draw()
    bool m_canselectelement;        //If set to true, it is possible to select an element of the list by clicking on it. The selection is marked by a red rectangle.
};

#endif