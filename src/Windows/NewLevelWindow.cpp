#include "NewLevelWindow.h"

#include "../Editor.h"
#include "../GUI/Widget/Button.h"
#include "../GUI/Widget/IntField.h"
#include "../GUI/Widget/Label.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/Window.h"
#include "../GUI/WindowManager.h"
#include "WinIDs.h"

extern Editor* g_editor;

void CreateGrid(Button* but) {
    NewLevelWindow* win = (NewLevelWindow*)(but->m_parrent->m_window);
    g_editor->CreateNewLevel(win->m_vargridwidth, win->m_vargridheight, win->m_varboxwidth, win->m_varboxheight);
    g_editor->m_winmanager->Remove(win);
}

NewLevelWindow::NewLevelWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_NEWLEVEL;
    SetPosition(100, 100);

    m_titlebartext = "New level";

    m_width = 205;
    m_height = 111;

    //default values
    m_vargridwidth = 16;
    m_vargridheight = 16;
    m_varboxwidth = 16;
    m_varboxheight = 16;


    //Labels
    m_widgetmanager->Add(new Label(m_widgetmanager, 3, 15, "Grid Width :"));
    m_widgetmanager->Add(new Label(m_widgetmanager, 3, 33, "Grid Height :"));
    m_widgetmanager->Add(new Label(m_widgetmanager, 3, 51, "Box Width (in pixel) :"));
    m_widgetmanager->Add(new Label(m_widgetmanager, 3, 69, "Box Height (in pixel) :"));


    //IntFields
    IntField* gridwidthfield = new IntField(m_widgetmanager,  115, 15, 87, &m_vargridwidth);
    IntField* gridheightfield = new IntField(m_widgetmanager, 115, 33, 87, &m_vargridheight);
    IntField* boxwidthfield = new IntField(m_widgetmanager,   115, 51, 87, &m_varboxwidth);
    IntField* boxheightfield = new IntField(m_widgetmanager,  115, 69, 87, &m_varboxheight);

    gridwidthfield->AllowNegative(false);  gridwidthfield->SetMinMax(1, 65535);
    gridheightfield->AllowNegative(false); gridheightfield->SetMinMax(1, 65535);
    boxwidthfield->AllowNegative(false);   boxwidthfield->SetMinMax(1, 65535);
    boxheightfield->AllowNegative(false);  boxheightfield->SetMinMax(1, 65535);

    m_widgetmanager->Add(gridwidthfield);
    m_widgetmanager->Add(gridheightfield);
    m_widgetmanager->Add(boxwidthfield);
    m_widgetmanager->Add(boxheightfield);


    //Button
    Button* confirmbutton = new Button(m_widgetmanager, 115, 92, 87, 16);
    confirmbutton->SetAction(CreateGrid);
    confirmbutton->SetText("Confirm");
    m_widgetmanager->Add(confirmbutton);
}