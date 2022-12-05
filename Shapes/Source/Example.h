#pragma once

#include "Application.h"

class Example : public Application
{
private:

	Camera* m_Camera = nullptr;
	Shapes::Rectangle* m_Rectangle = nullptr;
	Shapes::Circle* m_Circle = nullptr;
	Shapes::Triangle* m_Triangle = nullptr;
public:

	Example(const std::wstring& title = L"Example",
		const glm::ivec2& size = { 600, 600 },
		const glm::vec2& screenPixelsInBitMapPixels = { 1.0f, 1.0f });

	virtual void OnStart() override;

	virtual void OnUpdate() override;
	
	virtual void OnClose() override;
};

