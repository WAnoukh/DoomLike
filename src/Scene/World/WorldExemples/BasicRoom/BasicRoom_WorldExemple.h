#pragma once
#include "Scene/World/World.h"
#include "Scene/World/WorldGeometry/Edge.h"

class BasicRoom_WorldExemple : World
{
public:
    BasicRoom_WorldExemple()
    {
        AddEdge(new Edge(1.0f,1.0f,-1.0f,1.0f));
        AddEdge(new Edge(-1.0f,1.0f,-1.0f,-1.0f));
        AddEdge(new Edge(-1.0f,-1.0f,1.0f,-1.0f));
        AddEdge(new Edge(1.0f,-1.0f,1.0f,1.0f));

        Entity& player = GetPlayer();
        player.SetPosition(vec3(0,0,0));
    }
};
