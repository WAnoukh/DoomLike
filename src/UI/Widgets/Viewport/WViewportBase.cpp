#include "WViewportBase.h"
#include <glad/glad.h>
#include <imgui.h>

WViewportBase::~WViewportBase()
{
    glDeleteFramebuffers(1, &FBO);
}

void WViewportBase::Init()
{
    glGenFramebuffers(1, &FBO);
}

void WViewportBase::RenderUI()
{
    RenderViewPort();
    // Set all margins to 0 for the ImGui window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(guiName);
    isWindowHovered = ImGui::IsWindowHovered();
    windowSize = ImGui::GetContentRegionAvail();
    if (windowSize.x != lastSize.x || windowSize.y != lastSize.y) // NOLINT(clang-diagnostic-float-equal)
    {
        lastSize = windowSize;
    }
    const ImVec2 cursorPos = ImGui::GetCursorPos();
    const ImVec2 windowPos = ImGui::GetWindowPos();
    viewPortPos = ImVec2(cursorPos.x + windowPos.x, cursorPos.y + windowPos.y);
    ImGui::Image(ImTextureID(viewPortTexture), windowSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();
}

void WViewportBase::PreRenderViewPort()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    int width = static_cast<int>(lastSize.x), height = static_cast<int>(lastSize.y);

    glViewport(0, 0, width, height);

    glBindTexture(GL_TEXTURE_2D, viewPortTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, viewPortTexture, 0);

    glClearColor(0.20784313725490197f, 0.1843137254901961f, 0.26666666666666666f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WViewportBase::RenderViewPort()
{
    PreRenderViewPort();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ImVec2 WViewportBase::ScreenSpaceToViewportSpace(ImVec2 screenSpacePos)
{
    const auto viewPortPos = GetViewPortPos();
    return ImVec2(screenSpacePos.x - viewPortPos.x, screenSpacePos.y - viewPortPos.y);
}

bool WViewportBase::IsWindowHovered()
{
    return isWindowHovered;
}

const char* WViewportBase::GetGuiName()
{
    return guiName;
}

ImVec2 WViewportBase::GetViewPortPos()
{
    return viewPortPos;
}

ImVec2 WViewportBase::GetViewPortSize()
{
    return lastSize;
}

ImVec2 WViewportBase::GetWindowSize() const
{
    return windowSize;
}

ImVec2 WViewportBase::GetMousePosInViewport()
{
    const auto viewportPos = GetViewPortPos();
    const auto mousePos = ImGui::GetMousePos();
    return ImVec2(mousePos.x - viewportPos.x, mousePos.y - viewportPos.y);
}

void WViewportBase::SetViewPortTexture(unsigned inViewPortTexture)
{
    viewPortTexture = inViewPortTexture;
}
