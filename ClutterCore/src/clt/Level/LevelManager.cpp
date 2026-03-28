#include <clt/Core/Level/LevelManager.h>

#include "clt/Core/Meta/Serializer.h"

clt::LevelManager::LevelManager()
{
}

clt::LevelManager::~LevelManager()
{
    const meta::Serializer e(mLevel.get());

    e.Serialize(mActualLevelPath);
}

void clt::LevelManager::Update(const double dt)
{
    if (mLevel)
    {
        if (mLevelState == LevelState::Play)
        {
            mLevel->UpdatePhysics(dt);
            mLevel->UpdateScripts(dt);
        }

        mLevel->Render();
    }

    if (mAsyncLoadingLevel)
    {
        mAsyncLoadingLevel = false;

        // TODO : wait mutex until the level is loaded
    }
    else if (!mPendingLevelPath.empty())
    {
        auto newLevel = std::make_unique<clt::Level>();

        if (const meta::Serializer e(newLevel.get()); e.Deserialize(mPendingLevelPath))
        {
            mLevel.reset();
            mLevel = std::move(newLevel);

            mActualLevelPath = mPendingLevelPath;
        }

        mPendingLevelPath.clear();
    }
}

void clt::LevelManager::OpenLevel(const std::string& path)
{
    mPendingLevelPath = path;
}

void clt::LevelManager::AsyncLoadLevel(const std::string& path, const std::string& loadingLevel)
{
    mAsyncLoadingLevel = true;
}

clt::Level* clt::LevelManager::GetCurrentLevel() const
{
    return mLevel.get();
}

void clt::LevelManager::SetLevelState(LevelState state)
{
    mLevelState = state;
}

clt::LevelState clt::LevelManager::GetLevelState() const
{
    return mLevelState;
}
