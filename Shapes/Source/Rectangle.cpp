#include "Rectangle.h"

#include "Window.h"

using namespace Shapes;

Rectangle::Rectangle(const glm::vec2& halfExtent)
{
	SetHalfExtent(halfExtent);
}

void Rectangle::Render(const Camera& camera)
{
	const glm::mat4 transform = m_Transform.GetTransform();
	const glm::mat4 viewProjection = camera.GetViewProjectionMat4();

	// Get the positions in clip space.
	glm::vec4 vertices[4];
	vertices[0] = viewProjection * transform * glm::vec4(-m_HalfExtent.x, -m_HalfExtent.y, 0.0f, 1.0f);
	vertices[1] = viewProjection * transform * glm::vec4(-m_HalfExtent.x,  m_HalfExtent.y, 0.0f, 1.0f);
	vertices[2] = viewProjection * transform * glm::vec4( m_HalfExtent.x,  m_HalfExtent.y, 0.0f, 1.0f);
	vertices[3] = viewProjection * transform * glm::vec4( m_HalfExtent.x, -m_HalfExtent.y, 0.0f, 1.0f);

	// Get the positions in pixels.
	for (size_t i = 0; i < 4; i++)
	{
		vertices[i] = camera.FromClipSpaceToScreenSpace(vertices[i]);
	}

	Window::GetInstance().DrawRectangle(
		glm::ivec2(vertices[0]),
		glm::ivec2(vertices[1]),
		glm::ivec2(vertices[2]),
		glm::ivec2(vertices[3]),
		m_Color);
}
