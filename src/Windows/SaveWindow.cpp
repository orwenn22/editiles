#include "SaveWindow.h"

#include "../GUI/Widget/Button.h"
#include "../GUI/Widget/CppStringField.h"
#include "../GUI/Widget/WidgetManager.h"
#include "../GUI/WindowManager.h"
#include "../Editor.h"
#include "../Level.h"
#include "WinIDs.h"

void SaveEditor_ButAction(Button* but) {
    SaveWindow* win = (SaveWindow*) but->m_parrent->m_window;

    if(win->m_savename.empty()) return;

    win->m_editor->m_level->Save(win->m_savename);
    win->m_editor->m_name = win->m_savename;

    win->m_parrent->Remove(win);

    printf("Level saved !\n");
}

SaveWindow::SaveWindow(Editor* editor) : Window() {
    m_editor = editor;
    m_savename = m_editor->m_name;

    m_id = WINID_SAVELEVEL;
    m_width = 200;
    m_height = 60;
    m_titlebartext = "Save room";

    m_widgetmanager->Add(new CppStringField(3, 13, 145, &m_savename));

    Button* confirmbut = new Button(3, 37, 50, 15);
    confirmbut->SetText("Save");
    confirmbut->SetAction(SaveEditor_ButAction);
    m_widgetmanager->Add(confirmbut);
}