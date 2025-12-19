#pragma once
#include <clt/Core/IWindow.h>
#include <clt/Renderer/GraphicContext.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "clt/Renderer/GraphicContext.h"

namespace clt
{
    class WindowsWindow : public IWindow
    {
        GLFWwindow* mWindowHandle;
        std::unique_ptr<graphic::context> mContext;

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;
            std::function<void()> EventCallback;
        };

        WindowData mData;

        public:

        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline uint32_t GetWidth() const override { return mData.Width; }
        inline uint32_t GetHeight() const override { return mData.Height; }

        inline void SetEventCallback(const std::function<void()>& callback) override { mData.EventCallback = callback; }
        virtual void* GetNativeWindow() const override { return mWindowHandle; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };
}
