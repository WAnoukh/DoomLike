#include "World.h"

#include <corecrt_math_defines.h>

#include "Helpers/UsefullFunc.h"
#include "Rays/Ray.h"
#include "WorldGeometry/Edge.h"

World::World()
{
    player.SetWorld(this);
}

World::~World()
{
    for(Edge*& edge : edges)
    {
        delete edge;
    }
    edges.clear();
}

void World::AddEdge(Edge* inEdge)
{
    edges.push_front(inEdge);
}

void World::AddEdge(Edge& inEdge)
{
    edges.push_front(&inEdge);
}

Entity& World::GetPlayer()
{
    return player;
}

const std::list<Edge*>& World::GetEdges() const
{
    return edges;
}

bool World::RayCastOnEdges(Ray ray, HitResult& hitResult, bool sorted)
{
    HitResult tempHitResult;
    bool hasHit = true;
    for(Edge*& edge : edges)
    {
        if(RayCastOnEdge(ray, edge, tempHitResult))
        {
            if(sorted)
            {
                if(hasHit || tempHitResult.distance < hitResult.distance)
                {
                    hitResult = tempHitResult;
                    hasHit = false;
                }
            }
            else
            {
                hitResult = tempHitResult;
                return true;
            }
        }
    }
    return !hasHit;
}

bool World::RayCastOnEdge(Ray ray, Edge* edge, HitResult& outHitResult)
{
    const float x1 = edge->GetStart().x;
    const float y1 = edge->GetStart().y;
    const float x2 = edge->GetEnd().x;
    const float y2 = edge->GetEnd().y;
    const float x3 = ray.origin.x;
    const float y3 = ray.origin.y;
    const float x4 = ray.origin.x + cos(ray.orientation);
    const float y4 = ray.origin.y + sin(ray.orientation);
    
    const float den = ( x1 - x2 ) * ( y3 - y4 ) - ( y1 - y2 ) * ( x3 - x4 );
    if(den == 0)  // NOLINT(clang-diagnostic-float-equal)
    {
        return false;
    }
    const float t = ( ( x1 - x3 ) * ( y3 - y4 ) - ( y1 - y3 ) * ( x3 - x4 ) ) / den;
    const float u = -( ( x1 - x2 ) * ( y1 - y3 ) - ( y1 - y2 ) * ( x1 - x3 ) ) / den;
    if(t > 0 && t < 1 && u > 0)
    {
        const float x = x1 + t * ( x2 - x1 );
        const float y = y1 + t * ( y2 - y1 );
        outHitResult.distance = sqrt(pow(x - x3, 2) + pow(y - y3, 2));
        outHitResult.edge = edge;
        outHitResult.point = vec2(x, y);
        return true;
    }
    return false;
}
