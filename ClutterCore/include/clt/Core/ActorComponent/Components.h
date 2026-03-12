#ifndef CLUTTERENGINE_COMPONENTS_H
#define CLUTTERENGINE_COMPONENTS_H

#include <clt/Core/Math/Math.h>

namespace clt
{
    struct Transform
    {
        Vector3 position{0.0f};
        Vector3 rotation{0.0f};
        Vector3 scale{1.0f};
    };
}

#endif //CLUTTERENGINE_COMPONENTS_H