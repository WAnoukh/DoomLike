#pragma once
#include "glm/glm.hpp"

using namespace glm;

class Edge
{
public:
    Edge(const vec2 p1, const vec2 p2): p1(p1), p2(p2) {}
    Edge(float x1, float y1, float x2, float y2): p1(x1,y1), p2(x2,y2) {}

    void SetPosition(unsigned int pointNb, vec2 position);

    const vec2 GetPosition(unsigned pointNb) const;

    const vec2 GetStart() const;

    const vec2 GetEnd() const;

private:
    vec2 p1 = vec2();
    vec2 p2 = vec2();
};
