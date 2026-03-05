#include <clt/Core/Event/Input/Input.h>
#include <clt/Core/Debug/Log.h>

clt::Input::Input() : mLastMousePosition({0.0f, 0.0f}), mScrollDelta(0.0f)
{
}

void clt::Input::OnEvent(Event& e)
{
}

void clt::Input::Update(float dt)
{
}

void clt::Input::BindAction(const std::string& name, EInputState state, std::function<void()> callback)
{
}

void clt::Input::BindAxis(const std::string& name, std::function<void(float)> callback)
{
}

bool clt::Input::IsKeyPressed(EKey key)
{

    return true;
}

bool clt::Input::IsMouseButtonPressed(EMouseButton button)
{

    return true;
}

bool clt::Input::OnKeyPressed(KeyPressedEvent& e)
{

    return true;
}

bool clt::Input::OnKeyReleased(KeyReleasedEvent& e)
{

    return true;
}

bool clt::Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{

    return true;
}

bool clt::Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
{

    return true;
}

bool clt::Input::OnMouseMoved(MouseMovedEvent& e)
{

    return true;
}

bool clt::Input::OnMouseScrolled(MouseScrollEvent& e)
{

    return true;
}
