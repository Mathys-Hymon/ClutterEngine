#pragma  once
#include <functional>
#include <string>
#include <vector>

#include "InputData.h"

namespace clt
{
    class Input
    {
    public:
        struct AxisMapping
        {
            EKey positiveKey;
            EKey negativeKey;
        };

        struct MouseAxisMapping
        {
            EMouseButton positiveKey;
            EMouseButton negativeKey;
        };

        struct VectMapping
        {
            EKey XpositiveKey;
            EKey XNegativeKey;

            EKey YpositiveKey;
            EKey YNegativeKey;
        };

        struct Action {
            std::string name;
            EInputState state;
            std::vector<std::function<void()>> callbacks;
        };

    private:
        std::unordered_map<EKey, std::vector<Action>> mKeyActionMap;
        std::unordered_map<EKey, bool> mPreviousKeyStates;

        std::unordered_map<std::string, AxisMapping> mAxisMap;
        std::unordered_map<std::string, std::vector<std::function<void(float)>>> mAxisCallbacks;

        std::unordered_map<std::string, VectMapping> mVectMap;
        std::unordered_map<std::string, std::vector<std::function<void(Vector2)>>> mVectCallbacks;


        // Mouse
        std::unordered_map<EMouseButton, std::vector<Action>> mMouseActionMap;
        std::unordered_map<EMouseButton, bool> mPreviousMouseStates;
        std::unordered_map<std::string, MouseAxisMapping> mMouseAxisMap;
        std::vector<std::function<void(Vector2)>> mMouseDeltaCallback;
        std::vector<std::function<void(float)>>   mMouseScrollCallback;

        Vector2 mLastMousePosition;
        Vector2 mScrollDelta;

        bool mShowMouse = false;
        bool mLockMouse = true;

        // Controller
        std::unordered_map<EControllerButton, std::vector<Action>> mControllerActionMap;
        std::unordered_map<EControllerButton, bool> mPreviousControllerStates;
        std::unordered_map<std::string, EControllerAxis> mControllerAxisMap;

        float mControllerDeadzone = 0.2f;

        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}