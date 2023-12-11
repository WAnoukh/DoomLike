#pragma once
#include "glm/glm.hpp"

using namespace glm;

class Edge
{
public:
    Edge(const vec2 p1, const vec2 p2): p1(p1), p2(p2) {};

    void SetPosition(unsigned int pointNb, vec2 position);

    const vec2 GetPosition(unsigned pointNb) const;

private:
    vec2 p1 = vec2();
    vec2 p2 = vec2();
};
