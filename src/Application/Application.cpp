#include "Application.h"
#include "Rendering/Textures/Texture.h"
#include "UI/Widgets/UIWidget.h"

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>
#include <imgui_internal.h>
#include <iostream>

#include "Rendering/Renderer/WorldRenderer/MinimapRenderer.h"
#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
#include "Rendering/Renderer/WorldRenderer/WorldEditorRenderer.h"
#include "Scene/World/WorldExemples/BasicRoom/BasicRoom_WorldExemple.h"
#include "UI/Widgets/Viewport/WSimpleViewport.h"
#include "UI/Widgets/Viewport/2DViewport/WTopDownWorldViewPort/WMinimapViewport.h"
#include "UI/Widgets/Viewport/2DViewport/WTopDownWorldViewPort/WWorldEditor.h"


void Application::Init() {
	if (Window.init() == -1) {
		std::cerr << "Application : Window.init() Failed." << std::endl;
	}
	glEnable(GL_DEPTH_TEST);

	basicRoom_WorldExemple = new BasicRoom_WorldExemple();
	
	minimapRenderer = new MinimapRenderer();
	minimapRenderer->SetWorldToRender(basicRoom_WorldExemple);
	minimapRenderer->Init();

	minimapViewPort = new WMinimapViewport();
	minimapViewPort->SetMinimapRenderer(minimapRenderer);
	AddWidget(minimapViewPort);

	worldEditorRenderer = new WorldEditorRenderer();
	worldEditorRenderer->SetWorldToRender(basicRoom_WorldExemple);
	worldEditorRenderer->Init();
	
	worldEditorWidget = new WWorldEditor();
	worldEditorWidget->SetWorldEditorRenderer(worldEditorRenderer);
	AddWidget(worldEditorWidget);
	
	gameRenderer = new GameRenderer();
	gameRenderer->SetWorldToRender(basicRoom_WorldExemple);
	gameRenderer->Init();

	gameViewPort = new WSimpleViewport("GameViewPort");
	gameViewPort->SetRenderer(gameRenderer);
	AddWidget(gameViewPort);
	
	playerController.Init();
	playerController.SetPlayer(&basicRoom_WorldExemple->GetPlayer());
}

void Application::Render()
{
	Window.PreRender();

	activeTexture.SendDataToOpenGl();
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	/*ImGuiViewport* guiViewPort = ImGui::GetMainViewport();  // NOLINT(clang-diagnostic-comment)
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiID dockspaceId = ImGui::DockSpaceOverViewport(guiViewPort,dockspaceFlags);
	if(LayoutNeedRefresh)
	{
		if (dockspaceId)
		{
			if(guiViewPort->Size.x != 0 && guiViewPort->Size.y != 0)
			{
				ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, guiViewPort->Size);
				
				auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.1f, nullptr, &dockspace_id);
				ImGui::DockBuilderDockWindow("Tools", dock_id_top);
				auto dock_id_top2 = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, nullptr, &dockspace_id);
				ImGui::DockBuilderDockWindow(textureEditor.GetGuiName(), dock_id_top2);
				ImGui::DockBuilderDockWindow(planeViewer.GetGuiName(), dockspace_id);
				ImGui::DockBuilderDockWindow(visualizer.GetGuiName(), dockspace_id);
			}
		}
		LayoutNeedRefresh = false;
	}	*/

	for( auto& Widget : UIWidgets)
	{
		Widget->RenderUI();
	}

	ImGui::Begin("Debug");
	float fov = gameRenderer->GetFov();
	ImGui::SliderFloat("Fov", &fov, 0.0f, 3.1415926f);
	gameRenderer->SetFov(fov);
	ImGui::End();
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	Window.PostRender();
}

void Application::Tick(float deltaTime)
{
	for (auto& Widget : UIWidgets)
	{
		Widget->Tick(deltaTime);
	}
	playerController.Tick(deltaTime);
}

Application& Application::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return *instance;
}

int Application::Run() {

	for (auto& Widget : UIWidgets)
	{
		Widget->Init();
	}
	float lastFrame = 0.0f;

	activeTexture.CreateBlankTexture(TEXTURE_W, TEXTURE_H, GL_RGB);
	activeTexture.GenerateOpenGlTexture();
	activeTexture.SendDataToOpenGl();
	
	// render loop
	// -----------
	while (!Window.shouldClose())
	{
		const auto currentFrame = static_cast<float>(glfwGetTime());
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		Tick(deltaTime);
		Render();
		
		glfwPollEvents();
	}
	Window.terminate();
	return 0;
}

void Application::framebufferSizeEvent()
{
	LayoutNeedRefresh = true;
}

void Application::AskForLayoutRefresh()
{
	LayoutNeedRefresh = true;
}

void Application::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset)
{
	for(auto& Widget : UIWidgets)
	{
		Widget->ScrollCallBackEvent(guiWantToCapture, xoffset, yoffset);
	}
}

void Application::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
{
	for(auto& Widget : UIWidgets)
	{
		Widget->MouseButtonCallBackEvent(guiWantToCapture, button, action, mods);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(action == GLFW_PRESS)
		{
			mouseRightPressed = true;
		}
		if(action == GLFW_RELEASE)
		{
			mouseRightPressed = false;
		}
	}
}

void Application::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
	//TODO: Replace that with Imgui::MousePos
	lastX = xPos;
	lastY = yPos;
	for(auto& Widget : UIWidgets)
	{
		Widget->MousePositionCallBackEvent(guiWantToCapture, xPos, yPos);
	}
}

void Application::KeyboardKeyCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int key, int scancode, int action,
	int mods)
{
	inputManager.KeyboardKeyCallBackEvent(key, scancode, action, mods);
}

void Application::AddWidget(UIWidget* widget)
{
	if(widget == nullptr)
	{
		std::cerr << "Application::AddWidget : widget is nullptr." << std::endl;
		return;
	}
	UIWidgets.push_back(widget);
	widget->Init();
}
