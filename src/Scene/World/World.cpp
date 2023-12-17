#include "World.h"
#include "WorldGeometry/Edge.h"
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
