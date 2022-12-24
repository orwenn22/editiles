#ifndef EDITOR_TABS_HANDLER_H
#define EDITOR_TABS_HANDLER_H

#include "GUI/TabsHandler.h"

class Application;

class EditorTabsHandler : public TabsHandler {
    public:
    EditorTabsHandler(Application* app);

    void SetSelectedTab(int value) override;     //called when a tab is left-clicked
    int GetSelectedTab() override;

    int GetTabCount() override;

    void OpenNewTab() override;
    void CloseTab(int value) override;

    std::string GetTabName(int value) override;
    void OnFileDragAndDrop(std::string filepath) override;

    Application* m_app;
};

#endif