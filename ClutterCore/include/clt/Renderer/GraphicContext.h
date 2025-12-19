#pragma once

namespace clt
{
    namespace graphic
    {
        class context
        {
        public:
            virtual ~context() = default;

            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
        };
    }
}