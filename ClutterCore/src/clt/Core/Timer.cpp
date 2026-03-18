
#include <clt/Core/Timer.h>
#include <algorithm>
#include <chrono>
#include <thread>

#include "clt/Core/Debug/Log.h"

std::chrono::steady_clock::time_point clt::Timer::mStartTime;
std::chrono::steady_clock::time_point clt::Timer::mLastTime;

std::unordered_map<std::string, double> clt::Timer::mChronos;

double clt::Timer::deltaTime = 0;
double clt::Timer::clampedDeltaTime = 0;

constexpr double maxDeltaTime = 0.006944f; // ~ 144 FPS

double clt::Timer::ComputeDeltaTime()
{
    const auto currentTime = std::chrono::steady_clock::now();
    const auto elapsedTime = std::chrono::duration<double>(currentTime - mLastTime);

    deltaTime = elapsedTime.count();

    clampedDeltaTime = std::min(deltaTime, maxDeltaTime);

    mLastTime = currentTime;

    return deltaTime;
}

void clt::Timer::Initialize()
{
    mStartTime = std::chrono::steady_clock::now();
}

void clt::Timer::DelayTime(const double seconds)
{
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

double clt::Timer::GetTimeSinceLoad()
{
    const auto currentTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsedTime = currentTime - mStartTime;

    return elapsedTime.count();
}

void clt::Timer::StartChrono(const std::string& name)
{
    mChronos[name] = GetTimeSinceLoad();
}

double clt::Timer::StopChrono(const std::string& name)
{
    if (!mChronos.contains(name))
    {
        CLT_CORE_WARN("No Chrono named {} exist", name);
        return 0;
    }

    const auto currentTime = GetTimeSinceLoad();
    const double startTime = mChronos[name];

    mChronos.erase(name);

    const auto elapsedTime = currentTime - startTime;

    return elapsedTime;
}
