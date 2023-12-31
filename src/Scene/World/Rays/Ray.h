﻿#pragma once
#include <glm/detail/type_vec2.hpp>

#include "Helpers/UsefullFunc.h"

class Edge;

struct Ray
{
    Ray(glm::vec2 origin, float orientation) : origin(origin), orientation(orientation)
    {
    }
    Ray(glm::vec2 origin, glm::vec2 end) : origin(origin)
    {
        orientation = AnoukhFun::Angle(origin, end);
    }
    
    glm::vec2 origin = glm::vec2(0, 0);
    float orientation = 0;
};

struct HitResult
{
    HitResult(bool hit, float distance, Edge* edge, glm::vec2 point) :
        distance(distance), edge(edge), point(point)
    {
    }
    HitResult() = default;
    float distance = 0;
    Edge* edge = nullptr;
    glm::vec2 point = glm::vec2(0, 0);
};
