#include <EditorUI/Panels/InspectorPanel.h>

#include "imgui.h"

#include "clt/Core/ActorComponent/Actor.h"
#include "clt/Core/ActorComponent/Components.h"
#include "clt/Core/Assets/IAssetManager.h"
#include "clt/Core/Assets/AssetType/Texture.h"
#include "clt/Core/Level/LevelManager.h"
#include "clt/Core/Meta/Reflection.h"

editor::InspectorPanel::InspectorPanel(EditorContext* context) : EditorPanel(context)
{
}

const char* editor::InspectorPanel::GetName() const
{
    return "Inspector";
}

editor::DockPosition editor::InspectorPanel::GetDockingPosition() const
{
    return DockPosition::right;
}

void editor::InspectorPanel::Draw()
{
    const auto selectedActor = mContext->selectedActor;

    if (! selectedActor) return;

    const auto level = mContext->engineContext->level->GetCurrentLevel();

    auto& [tagName] = level->Registry().get<clt::Name>(selectedActor->GetID());

    char buffer[256] = "";
    strncpy(buffer, tagName.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    if (ImGui::InputText( "##ActorNameInput", buffer, sizeof(buffer))) tagName = std::string(buffer);

    ImGui::Separator();

    auto& [pos, rot, scale] = level->Registry().get<clt::Transform>(selectedActor->GetID());

    // POS
    ImGui::DragFloat3("position", &pos.x, 0.01f);

    // ROT
    ImGui::DragFloat3("rotation", &rot.x, 0.01f);

    // SCALE
    ImGui::DragFloat3("scale", &scale.x, 0.01f);

    ImGui::Separator();

    for (auto [id, storage] : level->Registry().storage())
    {
        if (storage.contains(selectedActor->GetID()))
        {
            entt::meta_type metaType = entt::resolve(storage.info());
            if (!metaType) continue;

            const auto stringHash = metaType.id();

            std::string compName = clt::meta::GetName(stringHash);

            if (compName.empty() || compName == "Name" || compName == "Transform") continue;

            bool keepComponent = true;

            if (ImGui::CollapsingHeader(compName.c_str(), &keepComponent))
            {
                const auto voidVar = storage.value(selectedActor->GetID());

                auto var = metaType.from_void(voidVar);

                for (auto [ID, data] : metaType.data())
                {
                    std::string varName = clt::meta::GetName(ID);

                    ImGui::PushID(varName.c_str());

                    // VECTOR 3

                    if (data.type() == entt::resolve<clt::Vector3>())
                    {
                        auto propertyBox = data.get(var);
                        auto vec3 = propertyBox.cast<clt::Vector3>();

                        if (ImGui::DragFloat3(varName.c_str(), &vec3.x, 0.01f))
                        {
                            data.set(var, vec3);
                        }
                    }

                    // COLOR

                    if (data.type() == entt::resolve<clt::Color>())
                    {
                        auto propertyBox = data.get(var);
                        auto color = propertyBox.cast<clt::Color>();

                        if (ImGui::ColorEdit4(varName.c_str(), &color.r))
                        {
                            data.set(var, color);
                        }
                    }

                    // BOOL

                    if (data.type() == entt::resolve<bool>())
                    {
                        auto propertyBox = data.get(var);
                        auto b = propertyBox.cast<bool>();

                        if (ImGui::Checkbox(varName.c_str(), &b))
                        {
                            data.set(var, b);
                        }
                    }

                    // INT

                    if (data.type() == entt::resolve<int>())
                    {
                        auto propertyBox = data.get(var);
                        auto i = propertyBox.cast<int>();

                        if (ImGui::DragInt(varName.c_str(), &i))
                        {
                            data.set(var, i);
                        }
                    }

                    // CLAMPED INT

                    if (data.type() == entt::resolve<clt::ClampedInt>())
                    {
                        auto propertyBox = data.get(var);
                        auto [value, min, max] = propertyBox.cast<clt::ClampedInt>();

                        if (ImGui::SliderInt(varName.c_str(), &value, min, max))
                        {
                            data.set(var, clt::ClampedInt{value, min, max});
                        }
                    }

                    // FLOAT

                    if (data.type() == entt::resolve<float>())
                    {
                        auto propertyBox = data.get(var);
                        auto f = propertyBox.cast<float>();

                        if (ImGui::DragFloat(varName.c_str(), &f))
                        {
                            data.set(var, f);
                        }
                    }

                    // CLAMPED FLOAT

                    if (data.type() == entt::resolve<clt::ClampedFloat>())
                    {
                        auto propertyBox = data.get(var);
                        auto [value, min, max] = propertyBox.cast<clt::ClampedFloat>();

                        if (ImGui::SliderFloat(varName.c_str(), &value, min, max))
                        {
                            data.set(var, clt::ClampedFloat{value, min, max});
                        }
                    }

                    // UINT32

                    if (data.type() == entt::resolve<uint32_t>())
                    {
                        auto propertyBox = data.get(var);
                        auto ui = propertyBox.cast<uint32_t>();

                        uint32_t minVal = 0;

                        if (ImGui::DragScalar(varName.c_str(), ImGuiDataType_U32, &ui, 1.0f, &minVal, nullptr))
                        {
                            data.set(var, ui);
                        }
                    }

                    // STRING

                    if (data.type() == entt::resolve<std::string>())
                    {
                        auto propertyBox = data.get(var);
                        auto b = propertyBox.cast<std::string>();

                        char TextBuffer[256] = "";
                        strncpy(TextBuffer, b.c_str(), sizeof(TextBuffer));
                        buffer[sizeof(buffer) - 1] = '\0';

                        if (ImGui::InputText(varName.c_str(), TextBuffer, sizeof(TextBuffer)))
                        {
                            data.set(var, b);
                        }
                    }

                    // TEXTURE PATH

                    if (data.type() == entt::resolve<clt::TexturePath>())
                    {
                        auto propertyBox = data.get(var);
                        auto text = propertyBox.cast<clt::TexturePath>().path;

                        auto& allTex = mContext->engineContext->assets->GetAllTextures();

                        if (allTex.contains(text))
                        {
                            ImGui::Image(allTex.find(text)->second->GetID(), ImVec2(24, 24));
                            ImGui::SameLine();
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4.0f);
                        }

                        std::string shortName = text.empty() ? "None" : std::filesystem::path(text).stem().string();

                        if (ImGui::BeginCombo(varName.c_str(), shortName.c_str(), ImGuiComboFlags_HeightLarge))
                        {
                            static char TextBuffer[256] = "";

                            ImGui::InputTextWithHint("##SearchCombo", "find texture...", TextBuffer, sizeof(TextBuffer));
                            ImGui::Separator();

                            auto filterLower = std::string(TextBuffer);
                            for (auto& c : filterLower) c = static_cast<char>(std::tolower(c));

                            if (ImGui::BeginChild("##ComboList", ImVec2(0, 200)))
                            {
                                ImGui::PushID("NoneBtn");

                                if (const auto noneSelected = text.empty(); ImGui::Selectable("##invisibleBtn", noneSelected, ImGuiSelectableFlags_AllowOverlap, ImVec2(0, 32)))
                                {
                                    data.set(var, clt::TexturePath{""});
                                    ImGui::CloseCurrentPopup();

                                    ImGui::SameLine();

                                    ImGui::Image(mContext->engineContext->assets->LoadTexture(clt::PathType::engine, "Textures/default256.png")->GetID(), ImVec2(32, 32));

                                    ImGui::SameLine();

                                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
                                    ImGui::Text("None");

                                    if (noneSelected) ImGui::SetItemDefaultFocus();
                                }
                                ImGui::PopID();

                                for (const auto& [path, tex] : allTex)
                                {
                                    std::string texName = std::filesystem::path(path).stem().string();
                                    std::string texLower = texName;
                                    for (auto& c : texLower) c = static_cast<char>(std::tolower(c));

                                    if (!filterLower.empty() && texLower.find(filterLower) == std::string::npos) continue;

                                    ImGui::PushID(path.c_str());

                                    const bool isSelected = (text == path);

                                    if (ImGui::Selectable("##invisibleBtn", isSelected, ImGuiSelectableFlags_AllowOverlap, ImVec2(0, 32)))
                                    {
                                        data.set(var, clt::TexturePath{path});
                                        ImGui::CloseCurrentPopup();
                                    }
                                    ImGui::SameLine();

                                    ImGui::Image(tex->GetID(), ImVec2(32, 32));

                                    ImGui::SameLine();
                                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
                                    ImGui::TextUnformatted(texName.c_str());

                                    if (isSelected) ImGui::SetItemDefaultFocus();

                                    ImGui::PopID();
                                }
                            }
                            ImGui::EndChild();
                            ImGui::EndCombo();
                        }

                        if (ImGui::IsItemHovered()) ImGui::SetTooltip("%s", text.c_str());
                    }
                    ImGui::PopID();
                }
            }

            if (!keepComponent)
            {
                auto removeComp = metaType.func(entt::hashed_string{"RemoveComponent"});
                removeComp.invoke({}, &level->Registry(), selectedActor->GetID());
            }
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Add Component", ImVec2(-1.0f, 30.0f))) ImGui::OpenPopup("AddComponentPopup");

    if (ImGui::BeginPopup("AddComponentPopup"))
    {
        static std::string searchFilter;

        char AddCompBuffer[256] = "";
        strncpy(AddCompBuffer, searchFilter.c_str(), sizeof(AddCompBuffer));
        buffer[sizeof(AddCompBuffer) - 1] = '\0';

        if (ImGui::InputText( "##AddCompInput", AddCompBuffer, sizeof(AddCompBuffer))) searchFilter = std::string(AddCompBuffer);

        ImGui::Separator();

        std::string filterLower = searchFilter;
        for (auto& c : filterLower) c = static_cast<char>(std::tolower(c));

        if (ImGui::BeginChild("##AddComponentList", ImVec2(0, 250)))
        {
            for (auto [typeId, metaType] : entt::resolve())
            {
                auto addFunc = metaType.func(entt::hashed_string{"AddDefaultComponent"});

                if (!addFunc) continue;

                std::string compName = clt::meta::GetName(metaType.id());

                if (compName.empty() || compName == "TagComponent" || compName == "Transform") continue;

                if (auto* storage = level->Registry().storage(typeId); storage && storage->contains(selectedActor->GetID())) continue;

                std::string compLower = compName;

                for (auto& c : compLower) c = static_cast<char>(std::tolower(c));
                if (!filterLower.empty() && compLower.find(filterLower) == std::string::npos) continue;

                if (ImGui::Selectable(compName.c_str()))
                {
                    addFunc.invoke({}, &level->Registry(), selectedActor->GetID());

                    searchFilter.clear();
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        ImGui::EndChild();
        ImGui::EndPopup();
    }
}
