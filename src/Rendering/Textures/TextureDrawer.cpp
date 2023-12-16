#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "TextureDrawer.h"
#include "Texture.h"
#include "Rendering/Color/DLColor.h"


void TextureDrawer::SetBindTexture(Texture* texture)
{
    bindTexture = texture;
}

Texture* TextureDrawer::GetBindTexture() const
{
    return bindTexture;
}

void TextureDrawer::DrawCircle(glm::ivec2 pos, int radius, DLColor color)
{
    DrawCircle(pos.x, pos.y, radius, color);
}

void TextureDrawer::DrawCircle(int x, int y, int radius, DLColor color)
{
    if (bindTexture == nullptr)
    {
        std::cerr << "TextureDrawer::DrawCircle: bindTexture is nullptr" << std::endl;
        return;
    }
    int x1, y1;

    for (int i = -radius; i < radius; i++)
    {
        for (int j = -radius; j < radius; j++)
        {
            x1 = x + i;
            y1 = y + j;
            if (i * i + j * j <= radius * radius * 0.9)
            {
                bindTexture->EditPixel(x1, y1, color);
            }
        }
    }
}

void TextureDrawer::DrawLine(int x1, int y1, int x2, int y2, DLColor color)
{
    if (bindTexture == nullptr)
    {
        std::cerr << "TextureDrawer::DrawCircle: bindTexture is nullptr" << std::endl;
        return;
    }
    if (x1 == x2)
    {
        for (int newY = std::min(y1, y2); newY <= std::max(y1, y2); newY++)
        {
            bindTexture->EditPixel(x1, newY, color);
        }
    }
    else
    {
        int minX, maxX, minY, maxY;
        if (x1 < x2)
        {
            minX = x1;
            maxX = x2;
            minY = y1;
            maxY = y2;
        }
        else
        {
            minX = x2;
            maxX = x1;
            minY = y2;
            maxY = y1;
        }

        float a = static_cast<float>(maxY - minY) / static_cast<float>(maxX - minX);
        int lastDrawedY = minY;
        for (int x = minX; x <= maxX; x++)
        {
            int newY = (x - minX) * a + minY;
            for (int y = std::min(newY, lastDrawedY) + 1; y < std::max(newY, lastDrawedY); y++)
            {
                bindTexture->EditPixel(x, y, color);
            }
            bindTexture->EditPixel(x, newY, color);
            lastDrawedY = newY;
        }
    }
}

void TextureDrawer::DrawLine(glm::ivec2 start, glm::ivec2 end, DLColor color)
{
    DrawLine(start.x, start.y, end.x, end.y, color);
}

void TextureDrawer::DrawLine(glm::ivec2 start, float direction, float length, DLColor color)
{
    DrawLine(start.x, start.y, direction, length, color);
}

void TextureDrawer::DrawLine(int startX, int startY, float direction, float length, DLColor color)
{
    if (bindTexture == nullptr)
    {
        std::cerr << "TextureDrawer::DrawLine: bindTexture is nullptr" << std::endl;
        return;
    }
    int x1, y1, x2, y2;
    x1 = startX;
    y1 = startY;
    x2 = startX + static_cast<int>(length * cos(direction));
    y2 = startY + static_cast<int>(length * sin(direction));
    DrawLine(x1, y1, x2, y2, color);
}

TextureDrawer& TextureDrawer::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureDrawer();
    }
    return *instance;
}
