#pragma once

class DLObject
{
public:
    virtual ~DLObject() = default;
    virtual void Init() = 0;
    virtual void Tick(float deltaTime) = 0;
};
