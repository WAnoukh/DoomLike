#include "UsefullFunc.h"
#include <cmath>
#include <stdlib.h>
#include <glm/detail/type_vec2.hpp>

namespace AnoukhFun
{
    float Damp(float current, float target, float smoothTime, float deltaTime)
    {
        return std::lerp(current, target, 1 - pow(smoothTime, deltaTime));
    }

    int RandomInt(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    float RandomFloat(float min, float max)
    {
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }

    float Angle(glm::vec2 a, glm::vec2 b)
    {
        glm::vec2 c = b - a;
        return atan2(c.y, c.x);
    }
}
