#ifndef CLUTTERENGINE_LEVELMANAGER_H
#define CLUTTERENGINE_LEVELMANAGER_H
#include <memory>

#include "Level.h"

namespace clt
{
    enum class LevelState { Play, Paused };
    class LevelManager
    {
        std::unique_ptr<Level> mLevel{nullptr};
        std::string mActualLevelPath;
        std::string mPendingLevelPath;
        bool mAsyncLoadingLevel{false};

        LevelState mLevelState{LevelState::Play};

        public:
        LevelManager();
        ~LevelManager();

        void Update(double dt);
        void OpenLevel(const std::string& path);
        void AsyncLoadLevel(const std::string& path, const std::string& loadingLevel);

        Level* GetCurrentLevel() const;

        void SetLevelState(LevelState state);
        LevelState GetLevelState() const;
    };
}

#endif //CLUTTERENGINE_LEVELMANAGER_H