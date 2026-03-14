#ifndef CLUTTERENGINE_ASSETHANDLE_H
#define CLUTTERENGINE_ASSETHANDLE_H
#include <cstdint>
#include <string>
#include <unordered_map>
#include <entt/core/hashed_string.hpp>

class AssetHandle
{
    std::unordered_map<uint32_t, std::string> HashedToString;
    std::unordered_map<std::string, uint32_t> StringToHash;

public:
    AssetHandle() = default;
    AssetHandle(const AssetHandle&) = default;

    void RegisterTexture(const std::string& name, const uint32_t& hashedName)
    {
        if (name.empty()) return;

        HashedToString[hashedName] = name;
        StringToHash[name] = hashedName;
    }

    uint32_t GetHashFromName(const std::string& name)
    {
        if (const auto hash = StringToHash.find(name); hash != StringToHash.end()) return hash->second;
        else return 0;
    }
    std::string GetNameFromHash(const uint32_t hash)
    {
        if (const auto name = HashedToString.find(hash); name != HashedToString.end()) return name->second;
        else return "";
    }
};

#endif //CLUTTERENGINE_ASSETHANDLE_H