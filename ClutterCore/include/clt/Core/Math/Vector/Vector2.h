#pragma once
#include <algorithm>
#include "cmath"
#include <glm/glm.hpp>
#include "string"

struct Vector2
{
    float x = 0; // The x-coordinate of the vector.
    float y = 0; // The y-coordinate of the vector.

    static const Vector2 Zero; // A vector with both coordinates set to zero.
    static const Vector2 One;  // A vector with both coordinates set to one.

    Vector2() : x(0), y(0) {}

    // Constructor initializing the vector to (pX, pY).
    Vector2(const float pX,const float pY) : x(pX), y(pY) {}

    Vector2(const int pX,const int pY) : x(pX), y(pY) {}

    Vector2(const uint32_t pX, const uint32_t pY) : x(pX), y(pY) {}

    Vector2(const float pXY) : x(pXY), y(pXY) {}

    // Adds the components of another vector to this vector.
    inline void operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
    }

    // Adds a scalar to both components of the vector.
    inline void operator+=(const float length)
    {
        x += length;
        y += length;
    }

    // Subtracts the components of another vector from this vector.
    inline void operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
    }

    // Subtracts a scalar from both components of the vector.
    inline void operator-=(const float length)
    {
        x -= length;
        y -= length;
    }

    // Multiplies the components of this vector by another vector.
    inline void operator*=(const Vector2& multiplier)
    {
        x *= multiplier.x;
        y *= multiplier.y;
    }

    // Multiplies both components of the vector by a scalar.
    inline void operator*=(const float length)
    {
        x *= length;
        y *= length;
    }

    // Divides the components of this vector by another vector.
    inline void operator/=(const Vector2& divider)
    {
        x /= divider.x;
        y /= divider.y;
    }

    // Divides both components of the vector by a scalar.
    inline void operator/=(const float length)
    {
        x /= length;
        y /= length;
    }

    // Assigns the components of another vector to this vector.
    inline void operator=(const Vector2& newVec)
    {
        x = newVec.x;
        y = newVec.y;
    }

    // Negates the vector.
    inline Vector2 operator-() const
    {
        return { -x, -y };
    }

    // Checks if two vectors are equal.
    friend bool operator==(const Vector2& left, const Vector2& right)
    {
        return (left.x == right.x && left.y == right.y);
    }

    // Checks if vector length is equal to float.
    friend bool operator==(const Vector2& left, const float right)
    {
        return left.Length() == right;
    }

    // Checks if two vectors are not equal.
    friend bool operator!=(const Vector2& left, const Vector2& right)
    {
        return (left.x != right.x && left.y != right.y);
    }

    // Subtracts two vectors.
    friend Vector2 operator-(const Vector2& left, const Vector2& right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    // Subtracts a scalar from a vector.
    friend Vector2 operator-(const Vector2& left, const float right)
    {
        return { left.x - right, left.y - right };
    }

    // Subtracts a scalar from a vector.
    friend Vector2 operator-(const float left, const Vector2& right)
    {
        return { right.x - left, right.y - left };
    }

    // Adds two vectors.
    friend Vector2 operator+(const Vector2 left, const Vector2& right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    // Adds a scalar to a vector.
    friend Vector2 operator+(const Vector2& left, const float right)
    {
        return { left.x + right, left.y + right };
    }

    // Adds a scalar to a vector.
    friend Vector2 operator+(const float left,const Vector2& right)
    {
        return { left + right.x, left + right.y };
    }

    // Multiplies a vector by a scalar.
    friend Vector2 operator*(const float scalar, const Vector2& right)
    {
        return { scalar * right.x, scalar * right.y };
    }

    // Multiplies a vector by a scalar.
    friend Vector2 operator*(const Vector2& left, const float scalar)
    {
        return { left.x * scalar, left.y * scalar };
    }

    // Multiplies two vectors component-wise.
    friend Vector2 operator*(const Vector2& left, const Vector2& right)
    {
        return { left.x * right.x, left.y * right.y };
    }

    // Divides a scalar by a vector.
    friend Vector2 operator/(const float scalar, const Vector2& right)
    {
        return { scalar / right.x, scalar / right.y };
    }

    // Divides a vector by a scalar.
    friend Vector2 operator/(const Vector2& left, const float scalar)
    {
        return { left.x / scalar, left.y / scalar };
    }

    // Divides two vectors component-wise.
    friend Vector2 operator/(const Vector2& left, const Vector2& right)
    {
        return { left.x / right.x, left.y / right.y };
    }

    // Calculates the length of the vector.
    inline float Length() const
    {
        return sqrt(x * x + y * y);
    }

    // Checks if two vectors are equal within an acceptance range.
    inline bool Equal(const Vector2& right, const double acceptance) const
    {
        if (x < right.x - acceptance || x > right.x + acceptance || y < right.y - acceptance || y > right.y + acceptance) return false;
        else return true;
    }

    // Normalizes the vector to a unit vector.
    inline Vector2 Normalized() const
    {
        const float length = Length();
        if (length == 0) return Vector2(0, 0); // Handle division by zero
        Vector2 temp = *this;
        temp /= length;
        return temp;
    }

    // Calculates the squared distance between two vectors.
    static float DistanceSquared(const Vector2& left, const Vector2& right)
    {
        const float dx = left.x - right.x;
        const float dy = left.y - right.y;

        return dx * dx + dy * dy;
    }

    // Linearly interpolates between two vectors.
    static Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
    {
        return start + t * (end - start);
    }

    // Calculates the squared length of the vector.
    inline float LengthSquared() const
    {
        return x * x + y * y;
    }

    // Calculates the cross product of two vectors.
    inline float Cross(const Vector2& other) const
    {
        return x * other.y - y * other.x;
    }

    // Calculates the dot product of two vectors.
    static float Dot(const Vector2& left, const Vector2& right)
    {
        return left.x * right.x + left.y * right.y;
    }

    // Clamps the vector components to the given range.
    inline void Clamp(const float minValue, const float maxValue)
    {
        if (this->x < minValue)  this->x = minValue;
        if (this->x > maxValue) this->x = maxValue;

        if (this->y < minValue)  this->y = minValue;
        if (this->y > maxValue)  this->y = maxValue;
    }

    // Linearly interpolates between two vectors.
    static Vector2 VInterp(const Vector2& current, const Vector2& target, const float deltaTime, const float interpSpeed)
    {
        if (interpSpeed <= 0.0f)
        {
            return target;
        }
        Vector2 result = current + (target - current) * std::clamp(deltaTime * interpSpeed, 0.0f, 1.0f);
        return result;
    }

    // Clamps the vector components to the given range.
    friend Vector2 Clamp(Vector2 temp, const float minValue, const float maxValue)
    {
        if (temp.x < minValue)  temp.x = minValue;
        if (temp.x > maxValue)  temp.x = maxValue;

        if (temp.y < minValue)  temp.y = minValue;
        if (temp.y > maxValue)  temp.y = maxValue;

        return temp;
    }

    // Converts the vector to a string representation.
    inline std::string ToString() const
    {
        return " (" + std::to_string(x) + " , " + std::to_string(y) + ") ";
    }

    // Converts the vector to a glm::vec2.
    inline glm::vec2 ToGlm() const
    {
        return glm::vec2(x, y);
    }
};