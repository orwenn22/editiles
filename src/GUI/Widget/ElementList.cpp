#include "ElementList.h"

#include "../../Mouse/MouseObject.h"

extern MouseObject* g_mouse;

ElementList::ElementList(WidgetManager* widgetmanager, int x, int y, int w, int h) : Widget(widgetmanager, x, y, w, h) {
    m_firstelementindex = 0;
    m_elementheight = 30;
    m_canselectelement = false;
}

void ElementList::Update() {
    if(g_mouse->m_havebeenused == false) {
        if(g_mouse->m_x >= m_x && g_mouse->m_x < m_x+m_width
        && g_mouse->m_y >= m_y && g_mouse->m_y < m_y+m_height) {    //mouse on widget
            PreInputCheck();

            //Right Click
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                int clickindex = (g_mouse->m_y-m_y) / m_elementheight + m_firstelementindex;
                if(clickindex < GetElementCount()) {    //click is valid
                    printf("right click on index %i\n", clickindex);
                    RightClickOn(clickindex);
                }
            }
            //Left Click
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int clickindex = (g_mouse->m_y-m_y) / m_elementheight + m_firstelementindex;
                if(clickindex < GetElementCount()) {    //click is valid
                    printf("left click on index %i\n", clickindex);
                    LeftClickOn(clickindex);
                }
            }
            //Right Release
            if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                int releaseindex = (g_mouse->m_y-m_y) / m_elementheight + m_firstelementindex;
                if(releaseindex < GetElementCount()) {    //click is valid
                    printf("right release on index %i\n", releaseindex);
                    RightReleaseOn(releaseindex);
                }
            }
            //Left Release
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                int releaseindex = (g_mouse->m_y-m_y) / m_elementheight + m_firstelementindex;
                if(releaseindex < GetElementCount()) {    //click is valid
                    printf("left release on index %i\n", releaseindex);
                    LeftReleaseOn(releaseindex);
                }
            }

            //scroll
            m_firstelementindex-= (int)GetMouseWheelMove();

            g_mouse->m_havebeenused = true;
        }
    }

    if(m_firstelementindex >= GetElementCount()) {
        m_firstelementindex = GetElementCount()-1;
    }
    
    if(m_firstelementindex < 0) {
        m_firstelementindex = 0;
    }
}

void ElementList::Draw() {
    DrawRectangle(m_x, m_y, m_width, m_height, BLACK);
    DrawRectangleLines(m_x, m_y, m_width, m_height, WHITE);


    int painterx = m_x;
    int paintery = m_y;

    for(int i = m_firstelementindex; (i < GetElementCount()) && (i < m_firstelementindex + (m_height/m_elementheight)); i++) {
        DrawElement(painterx, paintery, i);
        DrawLine(m_x, paintery+m_elementheight-1, m_x+m_width-6, paintery+m_elementheight-1, WHITE);
        
        //DrawLine(m_x, paintery+29, m_x+m_width-6, paintery+29, WHITE);
        paintery += m_elementheight;
    }

    if(m_canselectelement) {
        //outline arount selected element
        if(GetSelectedElement() >= m_firstelementindex && GetSelectedElement() < m_firstelementindex+(m_height/m_elementheight)) {
            int yorigin = (GetSelectedElement() - m_firstelementindex) * 30 + 2;
            DrawRectangleLines(m_x+2, m_y+yorigin, m_width-10, 25, RED);
        }
    }

    //vertical line
    DrawLine(m_x+m_width-6, m_y, m_x+m_width-6, m_y+m_height, WHITE);

    //scrollbar
    if(GetElementCount() > 0) {
        int scrollbarx = m_x+m_width-5;
        int scrollbary = m_y+2+(((m_height-4)/GetElementCount()))*m_firstelementindex;
        
        //                                                                   V number of elements that can be displayed
        int scrollbarheight = ((m_height-4)/GetElementCount())*(m_height/m_elementheight);

        if(scrollbary+scrollbarheight>m_y+m_height-2) {
            scrollbarheight = (m_y+m_height-2) - scrollbary;    //don't cross the bottom of the scrollbar area
        }

        DrawRectangle(scrollbarx, scrollbary, 3, scrollbarheight, WHITE);
    }
}

//Return the number of element in the list. Need to be overrided in subclass.
int ElementList::GetElementCount() { return 0; }

//called when an element in the list is right clicked.
void ElementList::RightClickOn(int clickindex) { printf("rightclick | clickindex %i\n", clickindex); }
//called when an element in the list is left clicked.
void ElementList::LeftClickOn(int clickindex) { printf("leftclick | clickindex %i\n", clickindex); }
//called when an element in the list is right released.
void ElementList::RightReleaseOn(int releaseindex) { printf("rightrelease | releaseindex %i\n", releaseindex); }
//called when an element in the list is left released.
void ElementList::LeftReleaseOn(int releaseindex) { printf("leftrelease | releaseindex %i\n", releaseindex); }

//called when drawing an element of the list
void ElementList::DrawElement(int painterx, int paintery, int elementindex) {
    DrawText("Element lol", painterx+3, paintery+10, 10, WHITE);
}

//need to be overrided
int ElementList::GetSelectedElement() {
    return 0;
}

//need to be overrided
void ElementList::SetSelectedElement(int newselection) {
    return;
}

//called when mouse is over the widget. Override to add custom behavior to widget.
void ElementList::PreInputCheck() {
    return;
}