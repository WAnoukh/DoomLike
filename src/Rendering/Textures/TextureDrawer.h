#pragma once
#include <glm/vec2.hpp>

struct DLColor;
class Texture;

class TextureDrawer
{
public:

    void SetBindTexture(Texture* texture);
    [[nodiscard]] Texture* GetBindTexture() const;

    void DrawCircle(glm::ivec2 pos, int radius, DLColor color);
    
    void DrawCircle(int x, int y, int radius, DLColor color);

    void DrawLine(int x1, int y1, int x2, int y2, DLColor color);

    void DrawLine(glm::ivec2 start, glm::ivec2 end, DLColor color);

    void DrawLine(glm::ivec2 start, float direction, float length, DLColor color);

    void DrawLine(int startX, int startY, float direction, float length, DLColor color);

    static TextureDrawer& GetInstance();
    
private:
    Texture* bindTexture = nullptr;
    inline static TextureDrawer* instance = nullptr;
};
