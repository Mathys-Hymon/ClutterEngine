#ifndef CLUTTERENGINE_TIMER_H
#define CLUTTERENGINE_TIMER_H

#include <chrono>
#include <thread>
#include <unordered_map>

namespace clt
{
    class Timer
    {
        static std::chrono::steady_clock::time_point mStartTime;
        static std::chrono::steady_clock::time_point mLastTime;

        static std::unordered_map<std::string, double> mChronos;

    public:
        Timer() = default;
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        static void Initialize();
        static double ComputeDeltaTime();
        static void DelayTime(double seconds);
        static double GetTimeSinceLoad();

        static void StartChrono(const std::string& name);
        static double StopChrono(const std::string& name);

        static double deltaTime;
        static double clampedDeltaTime;
    };
}

#endif
