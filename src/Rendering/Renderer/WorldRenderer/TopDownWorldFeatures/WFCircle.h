#pragma once
#include <glm/detail/type_vec2.hpp>

#include "WorldFeature.h"
#include "Rendering/Color/DLColor.h"

class WFCircle : public WorldFeature
{
public:
    WFCircle(glm::vec2 center, int radius, DLColor color) : center(center), radius(radius), color(color) {}

    void Draw(TopDownWorldRenderer* renderer) override;

    void SetCenter(glm::vec2 inCenter);
    void SetRadius(int inRadius);
    void SetColor(DLColor inColor);
private:
    glm::vec2 center = glm::vec2(0, 0);
    int radius = 0;
    DLColor color = DLColor(0, 0, 0);
};
