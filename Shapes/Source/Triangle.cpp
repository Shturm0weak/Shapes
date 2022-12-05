#include "Triangle.h"

#include "Window.h"

using namespace Shapes;

Triangle::Triangle(const glm::vec2 vertices[3])
{
	SetVertices(vertices);
}

void Triangle::Render(const Camera& camera)
{
	const glm::mat4 transform = m_Transform.GetTransform();
	const glm::mat4 viewProjection = camera.GetViewProjectionMat4();
	glm::vec4 vertices[3];

	for (size_t i = 0; i < 3; i++)
	{
		// Get the positions in clip space.
		vertices[i] = viewProjection * transform * glm::vec4(m_Vertices[i], 0.0f, 1.0f);
		
		// Get the positions in pixels.
		vertices[i] = camera.FromClipSpaceToScreenSpace(vertices[i]);
	}

	Window::GetInstance().DrawTriangle(
		glm::ivec2(vertices[0]),
		glm::ivec2(vertices[1]),
		glm::ivec2(vertices[2]), 
		m_Color);
}

void Triangle::SetVertices(const glm::vec2 vertices[3])
{
	for (size_t i = 0; i < 3; i++)
	{
		m_Vertices[i] = vertices[i];
	}
}

glm::vec2 Triangle::GetVertex(size_t i) const
{
	if (i < 3)
	{
		return m_Vertices[i];
	}
	
	return { 0.0f, 0.0f };
}
