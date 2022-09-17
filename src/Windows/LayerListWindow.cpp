#include "LayerListWindow.h"

#include "../Editor.h"
#include "../GUI/Widget/Button.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../Level.h"
#include "../Widget/LayerList.h"
#include "WinIDs.h"

extern Editor* g_editor;

void NewLayerButtonAction(Button* but) {
    g_editor->m_level->AddLayer("New layer");
}

LayerListWindow::LayerListWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_LAYERLIST;

    SetPosition(100, 100);

    m_titlebartext = "Layer list";

    m_width = 200;
    m_height = 200;

    m_widgetmanager->Add(new LayerList(m_widgetmanager, 3, 15, 194, 150));

    Button* newbut = new Button(m_widgetmanager, 3, 168, 50, 15);
    newbut->SetText("New");
    newbut->SetAction(NewLayerButtonAction);
    m_widgetmanager->Add(newbut);
}