#pragma once
#include <list>

#include "Entities/Player.h"

class Texture;
struct HitResult;
class Edge;
struct Ray;

class World
{
public:
    World();
    virtual ~World();

    Player& GetPlayer();
    const std::list<Edge*>& GetEdges() const;

    bool RayCastOnEdges(Ray ray, HitResult& outHitResult, bool sorted = false);
    static bool RayCastOnEdge(Ray ray, Edge* edge, HitResult& outHitResult);

    Texture* WallTexture;
protected:
    void AddEdge(Edge* inEdge);
    void AddEdge(Edge& inEdge);
private:
    std::list<Edge*> edges;
    Player player;
};
