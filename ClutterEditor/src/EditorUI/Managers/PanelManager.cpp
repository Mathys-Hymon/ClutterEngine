#include <EditorUI/Managers/PanelManager.h>

void editor::PanelManager::RegisterPanel(PanelPtr panel)
{
    if (!panel) return;

    if (const std::string& id = panel->GetID(); mPanelsById.contains(id))
    {
        std::string newID;

        do
        {
            constexpr int n = 1;
            newID = id + "_" + std::to_string(n);
        }
        while (mPanelsById.contains(newID));

        mPanelsById[newID] = panel.get();
        mPanels.push_back(std::move(panel));
        mIdOverrides[mPanels.back().get()] = newID;
    }
    else
    {
        mPanelsById[id] = panel.get();
        mPanels.push_back(std::move(panel));
    }
}

void editor::PanelManager::RegisterPanels(const std::vector<PanelPtr>& panels)
{
    for (auto& panel : panels) RegisterPanel(panel);
}

editor::EditorPanel* editor::PanelManager::FindByID(const std::string& id) const
{
    if (const auto it = mPanelsById.find(id); it != mPanelsById.end()) return it->second;

    return nullptr;
}

const std::string& editor::PanelManager::GetRegisteredID(EditorPanel* panel) const
{
    if (const auto it = mIdOverrides.find(panel); it != mIdOverrides.end()) return it->second;

    return panel ? panel->GetID() : std::string("");
 }
