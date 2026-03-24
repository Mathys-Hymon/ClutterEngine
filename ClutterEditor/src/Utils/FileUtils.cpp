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
        CLUTTER_ERROR("NFD folder picking closed: {}", NFD_GetError());
        return "";
    }

    return "";
}

std::string editor::utils::FileUtils::SelectFile(const char* filterName, const char* filterExt)
{
    const nfdfilteritem_t filterItem[1] = { { filterName, filterExt } };

    const nfdfilteritem_t* filterPtr = nullptr;
    nfdfiltersize_t filterCount = 0;

    if (filterName && filterExt)
    {
        filterPtr = filterItem;
        filterCount = 1;
    }

    nfdu8char_t* path = nullptr;

    if (const auto result = NFD_OpenDialogU8(&path, filterPtr, filterCount, nullptr); result == NFD_OKAY)
    {
        std::string finalPath = path;
        NFD_FreePathU8(path);
        return finalPath;
    }
    else if (result == NFD_CANCEL)
    {
        CLUTTER_INFO("File Picking Canceled");
        return "";
    }
    else if (result == NFD_ERROR)
    {
        CLUTTER_ERROR("NFD file picking closed: {}", NFD_GetError());
        return "";
    }

    return "";
}
