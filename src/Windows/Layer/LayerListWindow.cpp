#include "LayerListWindow.h"

#include "../../Editor.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../Layer/GridLayer.h"
#include "../../Layer/InstanceLayer.h"
#include "../../Level.h"
#include "../../Widget/LayerList.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void NewGridLayerButtonAction(Button* but) {
    Level* level = g_editor->m_level;
    level->AddLayer(new GridLayer(level->m_width, level->m_height, level, "newlayer"));
}

void NewInstLayerButtonAction(Button* but) {
    Level* level = g_editor->m_level;
    level->AddLayer(new InstanceLayer(level, "newlayer"));
}

LayerListWindow::LayerListWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_LAYERLIST;

    SetPosition(100, 100);

    m_titlebarcolor = {52, 98, 63, 255};
    m_titlebartext = "Layer list";

    m_width = 200;
    m_height = 200;

    m_widgetmanager->Add(new LayerList(m_widgetmanager, 3, 15, 194, 150));

    Button* newgridbut = new Button(m_widgetmanager, 3, 168, 50, 15);
    newgridbut->SetText("Grid");
    newgridbut->SetAction(NewGridLayerButtonAction);
    m_widgetmanager->Add(newgridbut);

    Button* newinstbut = new Button(m_widgetmanager, 56, 168, 50, 15);
    newinstbut->SetText("Instance");
    newinstbut->SetAction(NewInstLayerButtonAction);
    m_widgetmanager->Add(newinstbut);
}