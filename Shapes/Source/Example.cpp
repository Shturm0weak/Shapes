#include "Example.h"

#include "Window.h"
#include "Time.h"

Example::Example(const std::wstring& title, const glm::ivec2& size, const glm::vec2& screenPixelsInBitMapPixels)
	: Application(title, size, screenPixelsInBitMapPixels)
{

}

void Example::OnStart()
{
	Window& window = Window::GetInstance();
	m_Camera = window.CreateCamera();
	m_Camera->SetOrthographic(window.GetBitMapSize());
	m_Camera->SetZoom(5.0f);
	m_Scene.BindCamera(m_Camera);

	m_Rectangle = m_Scene.CreateRectangle({ 1, 1 });

	m_Circle = m_Scene.CreateCircle(1.0f, 0.0f);
	m_Circle->m_Color = { 0.0f, 1.0f, 0.0f };

	const glm::vec2 vertices[3] = { { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };
	m_Triangle = m_Scene.CreateTriangle(vertices);
	m_Triangle->m_Color = { 1.0f, 0.0f, 0.0f };

	m_Scene.CreateCircle(0.5f, 0.1f)->m_Transform.Translate({ 0.0f, 2.0f, 0.0f });
	m_Scene.CreateCircle(0.3f, 0.1f)->m_Transform.Translate({ 0.0f, 2.0f, 0.0f });
	m_Scene.CreateCircle(0.1f, 0.1f)->m_Transform.Translate({ 0.0f, 2.0f, 0.0f });
}

void Example::OnUpdate()
{
	//m_Camera->m_Transform.Translate(m_Camera->m_Transform.GetPosition() + glm::vec3(Time::GetDeltaTime()) * 0.5f);
	m_Triangle ->m_Transform.Rotate(m_Triangle->m_Transform.GetRotation() + glm::vec3(0.0f, 0.0f, Time::GetDeltaTime()));
	m_Rectangle->m_Transform.Rotate(m_Rectangle->m_Transform.GetRotation() - glm::vec3(0.0f, 0.0f, Time::GetDeltaTime()));
}

void Example::OnClose()
{
}

