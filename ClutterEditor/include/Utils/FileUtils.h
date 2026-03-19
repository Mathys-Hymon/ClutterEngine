#ifndef CLUTTERENGINE_FILEDIALOGS_H
#define CLUTTERENGINE_FILEDIALOGS_H
#include <string>

namespace editor::utils
{
    class FileUtils
    {
        public:

        static void Initialize();

        static std::string SelectFolder();
        static std::string SelectFile();
    };
}

#endif //CLUTTERENGINE_FILEDIALOGS_H