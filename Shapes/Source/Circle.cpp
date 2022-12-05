#include "Circle.h"

#include "Window.h"

using namespace Shapes;

Circle::Circle(float radius, float thickness)
{
	SetRadius(radius);
	SetThickness(thickness);
}

void Circle::Render(const Camera& camera)
{
	const glm::mat4 transform = m_Transform.GetTransform();
	const glm::mat4 viewProjection = camera.GetViewProjectionMat4();

	// Get the center position in clip space.
	glm::vec4 center = viewProjection * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Get the center position in pixels.
	center = camera.FromClipSpaceToScreenSpace(center);

	// Get the center + radius position in clip space.
	glm::vec4 radius = viewProjection * transform * glm::vec4(m_Radius, m_Radius, 0.0f, 1.0f);

	// Get the center + radius position in pixels.
	radius = camera.FromClipSpaceToScreenSpace(radius);

	if (m_Thickness > 0.0f)
	{
		// Get the center + thickness position in clip space.
		glm::vec4 thickness = viewProjection * transform * glm::vec4(m_Thickness, m_Thickness, 0.0f, 1.0f);

		// Get the center + thickness position in pixels.
		thickness = camera.FromClipSpaceToScreenSpace(thickness);

		Window::GetInstance().DrawCircle(center, radius.x - center.x, m_Color, thickness.x - center.x);
	}
	else
	{
		Window::GetInstance().DrawCircle(center, radius.x - center.x, m_Color);
	}
}
