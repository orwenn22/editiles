#include "LayerInfoWindow.h"

#include "../../Editor.h"
#include "../../Layer/Layer.h"
#include "../../Level.h"
#include "../../GUI/Widget/Button.h"
#include "../../GUI/Widget/CppStringField.h"
#include "../../GUI/Widget/Label.h"
#include "../../GUI/Widget/WidgetManager.h"
#include "../../GUI/WindowManager.h"
#include "../WinIDs.h"

extern Editor* g_editor;

void DeleteLayerButton(Button* but) {
    LayerInfoWindow* win = ((LayerInfoWindow*)(but->m_parrent->m_window));
    Layer* layer = win->m_layerpointer;

    //printf("%p\n", textureobject);
    g_editor->m_level->RemoveLayer(layer);
    g_editor->m_winmanager->Remove(win);
}

LayerInfoWindow::LayerInfoWindow(WindowManager* winmanager, Layer* layerptr) : Window(winmanager) {
    m_id = WINID_LAYERINFO;

    m_titlebarcolor = {52, 98, 63, 255};
    m_titlebartext = TextFormat("Layer %p", layerptr);

    m_height = 150;

    m_layerpointer = layerptr;

    //Name
    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 18, "Name :"));
    m_widgetmanager->Add(new CppStringField(m_widgetmanager , 40, 15, 107, &(m_layerpointer->m_name)));

    //Address
    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 32, TextFormat("Address : %p", m_layerpointer)));

    //Type
    m_widgetmanager->Add(new Label(m_widgetmanager, 5, 46, TextFormat("Layer type : %i", m_layerpointer->m_type)));

    //Delete button
    Button* deletebutton = new Button(m_widgetmanager, 5, 60, 50, 15);
    deletebutton->SetText("Delete");
    deletebutton->SetAction(DeleteLayerButton);
    m_widgetmanager->Add(deletebutton);
}