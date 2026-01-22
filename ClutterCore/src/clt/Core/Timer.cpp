
#include <clt/Core/Timer.h>
#include <algorithm>
#include <chrono>
#include <thread>

std::chrono::steady_clock::time_point clt::Timer::mStartTime;
std::chrono::steady_clock::time_point clt::Timer::mLastTime;

float clt::Timer::deltaTime = 0;
float clt::Timer::clampedDeltaTime = 0;

constexpr float maxDeltaTime = 0.033f; // 33ms ~ 30 FPS

float clt::Timer::ComputeDeltaTime()
{
    const auto currentTime = std::chrono::steady_clock::now();
    const auto elapsedTime = std::chrono::duration<float>(currentTime - mLastTime);

    deltaTime = elapsedTime.count();

    clampedDeltaTime = std::min(deltaTime, maxDeltaTime);

    mLastTime = currentTime;

    return deltaTime;
}

void clt::Timer::Initialize()
{
    mStartTime = std::chrono::steady_clock::now();
}

void clt::Timer::DelayTime(const float seconds)
{
    std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
}

float clt::Timer::GetTimeSinceLoad()
{
    const auto currentTime = std::chrono::steady_clock::now();
    const std::chrono::duration<float> elapsedTime = currentTime - mStartTime;

    return elapsedTime.count();
}
