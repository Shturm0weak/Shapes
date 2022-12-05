#pragma once

#include "Scene.h"

#include "../../Vendor/glm/glm.hpp"

#include <string>

class Application
{
public:

	Scene m_Scene;

	Application(const std::wstring& title = L"Application",
		const glm::ivec2& size = { 600, 600 },
		const glm::vec2& screenPixelsInBitMapPixels = { 1.0f, 1.0f });
	virtual ~Application() = default;

	virtual void OnStart() {};

	virtual void OnUpdate() {};

	virtual void OnClose() {};
};

