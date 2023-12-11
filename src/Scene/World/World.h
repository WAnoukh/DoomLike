#pragma once
#include <list>

#include "Entities/Entity.h"

class Edge;

class World
{
public:
    virtual ~World();

protected:
    void AddEdge(Edge* inEdge);
    void AddEdge(Edge& inEdge);

    Entity& GetPlayer();
private:
    std::list<Edge*> edges;
    Entity player;
};
