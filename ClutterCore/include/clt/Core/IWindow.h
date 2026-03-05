#ifndef CLUTTERENGINE_IWINDOW_H
#define CLUTTERENGINE_IWINDOW_H

#include <cstdint>
#include <functional>
#include  <string>

namespace clt
{
    struct WindowProps
    {
        std::string Title;
        uint32_t Width, Height;

        WindowProps(const std::string& title = "Clutter Engine",
            uint32_t width = 1280,
            uint32_t height = 720)
        : Title(title), Width(width), Height(height) {}
    };

    class IWindow
    {
    public:
        virtual ~IWindow()=default;

        virtual void OnUpdate() = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const std::function<void(class Event&)>& callback) = 0;
        virtual void* GetNativeWindow() const = 0;

        virtual void ResizeViewport(uint32_t startWidth, uint32_t startHeight, uint32_t width, uint32_t height) = 0;
        virtual void ResizeViewportCentered(uint32_t width, uint32_t height) = 0;
        virtual void RenameViewport(const char* name) = 0;
        virtual void SetVSync(bool enabled) = 0;

        static IWindow* Create(const WindowProps& props = WindowProps());

    };
}

#endif