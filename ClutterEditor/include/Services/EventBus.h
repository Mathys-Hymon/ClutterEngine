#ifndef CLUTTERENGINE_EVENTBUS_H
#define CLUTTERENGINE_EVENTBUS_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include <algorithm>
#include <cstdint>

namespace editor
{
    class EventBus
    {
    public:
        using Callback = std::function<void (const std::any&)>;

    private:
        struct Subscriber
        {
            uint32_t id;
            Callback cb;
        };

        std::unordered_map<std::string, std::vector<Subscriber>> mSubs;
        uint32_t mNextId{0};

    public:
        uint32_t Subscribe(const std::string& name, Callback cb)
        {
            const uint32_t id = ++mNextId;
            mSubs[name].push_back({id, std::move(cb)});
            return id;
        }

        void Unsubscribe(const std::string& name, uint32_t id)
        {
            const auto it = mSubs.find(name);
            if (it == mSubs.end()) return;
            auto& vec = it->second;

            std::erase_if(vec, [id](const Subscriber& s){ return s.id == id; });
        }

        void Publish(const std::string& name, const std::any& payload = {})
        {
            const auto it = mSubs.find(name);
            if (it == mSubs.end()) return;

            for (const auto& vec = it->second; auto& sub : vec)
            {
                if (sub.cb) sub.cb(payload);
            }
        }
    };
}

#endif //CLUTTERENGINE_EVENTBUS_H