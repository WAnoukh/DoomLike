#include "WorldRendererBase.h"
void WorldRendererBase::SetWorldToRender(World* inViewedWorld)
{
    worldToRender = inViewedWorld;
}

World* WorldRendererBase::GetWorldToRender() const
{
    return worldToRender;
}
