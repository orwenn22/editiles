#include "PaletteWindow.h"

#include "../Editor.h"
#include "../GUI/Widget/IntField.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../Level.h"
#include "../Widget/Palette.h"
#include "WinIDs.h"

extern Editor* g_editor;

PaletteWindow::PaletteWindow(WindowManager* winmanager) : Window(winmanager) {
    m_id = WINID_PALETTE;
    
    m_width = 300;
    m_height = 312;

    SetPosition(200, 200);

    IntField* palnumintfield = new IntField(m_widgetmanager, 5, 15, 120, &(g_editor->m_level->m_selectednumber));
    palnumintfield->AllowNegative(false);
    palnumintfield->SetMinMax(0, 65535);
    m_widgetmanager->Add(palnumintfield);

    m_widgetmanager->Add(new Palette(m_widgetmanager, 5, 35, 290, 260));
}