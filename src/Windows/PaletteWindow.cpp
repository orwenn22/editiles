#include "PaletteWindow.h"

#include "../Editor.h"
#include "../GUI/Widget/IntField.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../Level.h"
#include "../Widget/Palette.h"
#include "WinIDs.h"


PaletteWindow::PaletteWindow(Editor* editor) : Window() {
    m_id = WINID_PALETTE;
    
    m_width = 300;
    m_height = 312;

    SetPosition(200, 200);

    IntField* palnumintfield = new IntField(5, 15, 120, &(editor->m_level->m_selectednumber));
    palnumintfield->AllowNegative(false);
    palnumintfield->SetMinMax(0, 65535);
    m_widgetmanager->Add(palnumintfield);

    m_widgetmanager->Add(new Palette(5, 35, 290, 260, editor));
}