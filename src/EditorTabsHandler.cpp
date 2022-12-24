#include "EditorTabsHandler.h"

#include "Application.h"


EditorTabsHandler::EditorTabsHandler(Application* app) : TabsHandler() {
    m_app = app;
}

void EditorTabsHandler::SetSelectedTab(int value) {
    m_app->m_currenteditor = value;
}

int EditorTabsHandler::GetSelectedTab() {
    return m_app->m_currenteditor;
}


int EditorTabsHandler::GetTabCount() {
    return m_app->m_editorcount;
}

void EditorTabsHandler::OpenNewTab() {
    m_app->OpenNewLevelWindow();
}

void EditorTabsHandler::CloseTab(int value) {
    m_app->RemoveEditor(value);
}

#define MAXTABNAMESIZE 15
std::string EditorTabsHandler::GetTabName(int value) {
    std::string editorname = m_app->GetEditorName(value);
    if(editorname.length() < MAXTABNAMESIZE) {
        return editorname;
    }
    
    return "..." + editorname.substr(editorname.length() - MAXTABNAMESIZE);
}

void EditorTabsHandler::OnFileDragAndDrop(std::string filepath) {
    m_app->LoadFile(filepath);
}