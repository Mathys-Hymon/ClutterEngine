#ifndef CLUTTERENGINE_MATH_H
#define CLUTTERENGINE_MATH_H

#include "glm/fwd.hpp"
#include "glm/matrix.hpp"
#include "glm/vec2.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace clt
{
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;

    using UVector2 = glm::uvec2;
    using UVector3 = glm::uvec3;
    using UVector4 = glm::uvec4;

    using Color = glm::vec4;

    using Matrix3 = glm::mat3;
    using Matrix4 = glm::mat4;

    struct Matrix4Row
    {
        glm::mat4 Data{};

        explicit Matrix4Row(const Matrix4& colMajorMatrix)
        {
            Data = glm::transpose(colMajorMatrix);
        }

        const float* GetPointer() const
        {
            return glm::value_ptr(Data);
        }
    };

    namespace math
    {
        constexpr float PI = 3.14159265358979323846f;
        constexpr float HALF_PI = 1.57079632679489661923f;
        constexpr float TWO_PI = 6.28318530717958647692f;

        constexpr float FloatMax = std::numeric_limits<float>::max();
        constexpr float FloatMin = std::numeric_limits<float>::lowest();

        constexpr int IntMax = std::numeric_limits<int>::max();
        constexpr int IntMin = std::numeric_limits<int>::min();
    }

}

#endif //CLUTTERENGINE_MATH_H