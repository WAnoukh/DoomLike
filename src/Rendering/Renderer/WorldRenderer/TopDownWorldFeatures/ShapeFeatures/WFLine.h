#pragma once
#include <glm/detail/type_vec2.hpp>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldFeatures/WorldFeature.h"
#include "Rendering/Color/DLColor.h"

class WFLine : public WorldFeature
{
public:
    WFLine(glm::vec2 start, glm::vec2 end, DLColor color) : start(start), end(end), color(color) {}
    WFLine(glm::vec2 start, glm::vec2 end) : start(start), end(end) {}

    void Draw(TopDownWorldRenderer* renderer) override;

    void SetStart(glm::vec2 inStart);
    void SetEnd(glm::vec2 inEnd);
    void SetPositions(glm::vec2 inStart, glm::vec2 inEnd);
    void SetColor(DLColor inColor);
    
private:
    glm::vec2 start = glm::vec2(0, 0);
    glm::vec2 end = glm::vec2(0, 0);
    DLColor color = DLColor(0, 0, 0);  
};
