#include <Utils/FileUtils.h>
#include <nfd.hpp>

#include "clt/Core/Debug/Log.h"

void editor::utils::FileUtils::Initialize()
{
    NFD_Init();
}

std::string editor::utils::FileUtils::SelectFolder()
{
    nfdchar_t* path = nullptr;

    if(const auto result = NFD::PickFolder(path); result == NFD_OKAY)
    {
        std::string finalPath = path;
        NFD::FreePath(path);
        return finalPath;
    }
    else if (result == NFD_CANCEL)
    {
        CLUTTER_INFO("Folder Picking Canceled");
        return "";
    }
    else if (result == NFD_ERROR)
    {
        CLUTTER_ERROR("NFD Folder picking closed due to an unknown error");
        return "";
    }

    return "";
}
