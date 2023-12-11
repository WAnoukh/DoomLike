#pragma once
#include <list>

#include "Entities/Entity.h"

class Edge;

class World
{
public:

private:
    std::list<Edge*> edges;
    Entity player;
};
