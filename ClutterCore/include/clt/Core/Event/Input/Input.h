#pragma  once
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include <clt/Core/Math/Vector/Vector2.h>
#include "InputData.h"

#include "clt/Core/Event/Event.h"
#include "clt/Core/Event/KeyEvent.h"
#include "clt/Core/Event/MouseEvent.h"

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

    public:
        Input();
        ~Input() = default;

        void OnEvent(Event& e);
        void Update(float dt);

        void BindAction(const std::string& name, EInputState state, std::function<void()> callback);
        void BindAxis(const std::string& name, std::function<void(float)> callback);

        bool IsKeyPressed(EKey key);
        bool IsMouseButtonPressed(EMouseButton button);
        Vector2 GetMousePosition() const { return mLastMousePosition; }

    private:
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnKeyReleased(KeyReleasedEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrollEvent& e);

        std::unordered_map<EKey, bool> mKeyStates;
        std::unordered_map<EMouseButton, bool> mMouseStates;

        // --- Mapping ---
        std::unordered_map<EKey, std::vector<Action>> mKeyActionMap;

        std::unordered_map<std::string, AxisMapping> mAxisMap;
        std::unordered_map<std::string, std::vector<std::function<void(float)>>> mAxisCallbacks;

        // --- Mouse ---
        Vector2 mLastMousePosition{0,0};
        Vector2 mScrollDelta{0,0};
        std::vector<std::function<void(float)>> mMouseScrollCallbacks;

        bool mShowMouse = false;
        bool mLockMouse = true;

        float mControllerDeadZone = 0.2f;
    };
}