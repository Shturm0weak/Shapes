#include "Application.h"

#include "Window.h"

Application::Application(const std::wstring& title, const glm::ivec2& size, const glm::vec2& screenPixelsInBitMapPixels)
{
	Window::GetInstance().Init(title, size, screenPixelsInBitMapPixels);
}
