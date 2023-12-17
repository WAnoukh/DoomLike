#pragma once
#include <list>

#include "Entities/Entity.h"

class Edge;

class World
{
public:
    virtual ~World();

    Entity& GetPlayer();
    const std::list<Edge*>& GetEdges() const;
protected:
    void AddEdge(Edge* inEdge);
    void AddEdge(Edge& inEdge);
private:
    std::list<Edge*> edges;
    Entity player;
};
