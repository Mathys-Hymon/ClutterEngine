#ifndef CLUTTERENGINE_WINDOWMANAGER_H
#define CLUTTERENGINE_WINDOWMANAGER_H
#include <string>

namespace editor
{
    class WindowManager
    {
        public:

        WindowManager() = default;
        ~WindowManager() = default;

        void AddWindow(const std::string& name, bool isTab);
        void RemoveWindow(const std::string& name);
    };
}

#endif //CLUTTERENGINE_WINDOWMANAGER_H