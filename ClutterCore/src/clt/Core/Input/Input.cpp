#include <clt/Core/Event/Input/Input.h>
#include <clt/Core/Debug/Log.h>

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
}

bool clt::Input::IsMouseButtonPressed(EMouseButton button)
{
}

bool clt::Input::OnKeyPressed(KeyPressedEvent& e)
{
}

bool clt::Input::OnKeyReleased(KeyReleasedEvent& e)
{
}

bool clt::Input::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{
}

bool clt::Input::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
{
}

bool clt::Input::OnMouseMoved(MouseMovedEvent& e)
{
}

bool clt::Input::OnMouseScrolled(MouseScrollEvent& e)
{
}
