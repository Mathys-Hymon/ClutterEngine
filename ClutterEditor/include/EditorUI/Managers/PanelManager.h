#ifndef CLUTTERENGINE_PANELMANAGER_H
#define CLUTTERENGINE_PANELMANAGER_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "EditorUI/EditorPanel.h"

namespace editor
{
    class PanelManager
    {
    public:
        using PanelPtr = std::shared_ptr<EditorPanel>;

    private:
        std::vector<PanelPtr> mPanels;
        std::unordered_map<std::string, EditorPanel*> mPanelsById;
        std::unordered_map<EditorPanel*, std::string> mIdOverrides;

    public:
        void RegisterPanel(PanelPtr panel);
        void RegisterPanels(const std::vector<PanelPtr>& panels);

        const std::vector<PanelPtr>& GetPanels() const { return mPanels; }

        EditorPanel* FindByID(const std::string& id) const;
        const std::string& GetRegisteredID(EditorPanel* panel) const;
    };
}

#endif //CLUTTERENGINE_PANELMANAGER_H