#pragma once
#include <cmath>
#include <glm/detail/type_vec.hpp>

namespace AnoukhFun
{
    float Damp(float current, float target, float smoothTime, float deltaTime);

    template <typename T>
    T Lerp(T a, T b, float t)
    {
        return a + t * (b - a);
    }

    template <typename T>
    T Damp(T current, T target, float smoothTime, float deltaTime)
    {
        return Lerp(current, target, 1 - pow(smoothTime, deltaTime));
    }

    int RandomInt(int min, int max);

    float RandomFloat(float min, float max);

    float Angle(glm::vec2 a, glm::vec2 b);
}
