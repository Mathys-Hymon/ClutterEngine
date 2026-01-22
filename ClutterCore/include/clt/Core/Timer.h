#pragma once
#include <chrono>

namespace clt
{
    class Timer
    {
        static std::chrono::steady_clock::time_point mStartTime;
        static std::chrono::steady_clock::time_point mLastTime;

    public:
        Timer() = default;
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        static void Initialize();
        static float ComputeDeltaTime();
        static void DelayTime(float seconds);
        static float GetTimeSinceLoad();

        static float deltaTime;
        static float clampedDeltaTime;
    };
}
