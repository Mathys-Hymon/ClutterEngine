#ifndef CLUTTERENGINE_EDITORSERIALIZER_H
#define CLUTTERENGINE_EDITORSERIALIZER_H
#include <filesystem>

namespace editor
{
    struct EditorPreferences;

    class EditorSerializer
    {
    public:

        static bool LoadPreferences(EditorPreferences& outPrefs, const std::filesystem::path& engineRootPath);
        static void SavePreferences(const EditorPreferences& prefs, const std::filesystem::path& engineRootPath);
    };
}

#endif //CLUTTERENGINE_EDITORSERIALIZER_H