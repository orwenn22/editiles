#include "LayerInfoWindow.h"

#include "../Editor.h"
#include "../Level.h"
#include "../GridLayer.h"
#include "../GUI/Widget/Button.h"
#include "../GUI/Widget/CppStringField.h"
#include "../GUI/Widget/Label.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/WindowManager.h"
#include "WinIDs.h"

extern Editor* g_editor;

void DeleteLayerButton(Button* but) {
    LayerInfoWindow* win = ((LayerInfoWindow*)(but->m_parrent->m_window));
    GridLayer* layer = win->m_layerpointer;

    //printf("%p\n", textureobject);
    g_editor->m_level->RemoveLayer(layer);
    g_editor->m_winmanager->Remove(win);
}

LayerInfoWindow::LayerInfoWindow(WindowManager* winmanager, GridLayer* layerptr) : Window(winmanager) {
    m_id = WINID_LAYERINFO;
    m_titlebartext = TextFormat("Layer %p", layerptr);

    m_layerpointer = layerptr;

    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 18, "Name :"));
    m_widgetmanager->Add(new CppStringField(m_widgetmanager , 40, 15, 107, &(m_layerpointer->m_name)));

    Button* deletebutton = new Button(m_widgetmanager, 5, 32, 50, 15);
    deletebutton->SetText("Delete");
    deletebutton->SetAction(DeleteLayerButton);
    m_widgetmanager->Add(deletebutton);
}