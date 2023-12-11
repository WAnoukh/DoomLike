#include "Edge.h"

#include <iostream>

void Edge::SetPosition(unsigned int pointNb, vec2 position)
{
    switch (pointNb)
    {
    case 0:
        p1 = position;
        break;
    case 1:
        p2 = position;
        break;
    default:
        std::cerr << "pointNb do not correspond to an actual point" << std::endl;
    }
}

const vec2 Edge::GetPosition(unsigned pointNb) const
{
    switch (pointNb)
    {
    case 0:
        return p1;
    case 1:
        return p2;
    default:
        std::cerr << "pointNb do not correspond to an actual point" << std::endl;
        return vec2();
    }
}
