#pragma once
#include <clt/Core/IWindow.h>
#include <clt/Renderer/GraphicContext.h>

#ifdef CLUTTER_PLATFORM_WINDOWS

#include <GLFW/glfw3.h>
#include <memory>

namespace clt
{
    class WindowsWindow : public IWindow
    {
        GLFWwindow* mWindowHandle{};
        std::unique_ptr<graphic::context> mContext;

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;
            std::function<void(class Event&)> EventCallback;
        };

        WindowData mData;

        public:

        WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        uint32_t GetWidth() const override { return mData.Width; }
        uint32_t GetHeight() const override { return mData.Height; }
        UVector2 GetSize() const override { return {mData.Width, mData.Height}; };

        UVector2 GetMonitorSize() const override;

        inline void SetEventCallback(const std::function<void(Event&)>& callback) override { mData.EventCallback = callback; }
        void* GetNativeWindow() const override { return mWindowHandle; }

        void ResizeViewport(UVector2 pos, UVector2 size) override;
        void ResizeViewport(uint32_t startWidth, uint32_t startHeight, uint32_t width, uint32_t height) override;

        void ResizeViewportCentered(UVector2 size) override;
        void ResizeViewportCentered(uint32_t width, uint32_t height) override;
        void RenameViewport(const char* name) override;
        void SetVSync(bool enabled) override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
}

#endif