#include "Scene.h"

using namespace Shapes;

void Scene::Render(const Camera& camera)
{
	for (const auto& shape : m_ShapesById)
	{
		shape.second->Render(camera);
	}
}

void Scene::ShutDown()
{
	for (const auto& shape : m_ShapesById)
	{
		delete shape.second;
	}
}

Rectangle* Scene::CreateRectangle(const glm::vec2& halfExtent)
{
	Rectangle* rectangle = new Rectangle(halfExtent);
	rectangle->m_Id.Generate();
	m_ShapesById.emplace(rectangle->GetID(), rectangle);

	return rectangle;
}

Circle* Scene::CreateCircle(float radius, float thickness)
{
	Circle* circle = new Circle(radius, thickness);
	circle->m_Id.Generate();
	m_ShapesById.emplace(circle->GetID(), circle);

	return circle;
}

Triangle* Scene::CreateTriangle(const glm::vec2 vertices[3])
{
	Triangle* triangle = new Triangle(vertices);
	triangle->m_Id.Generate();
	m_ShapesById.emplace(triangle->GetID(), triangle);

	return triangle;
}

bool Scene::RemoveShape(const std::string& id)
{
	auto shape = m_ShapesById.find(id);
	if (shape != m_ShapesById.end())
	{
		delete shape->second;
		m_ShapesById.erase(id);

		return true;
	}

	return false;
}
