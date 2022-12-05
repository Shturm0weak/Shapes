#pragma once

#include "Camera.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

#include <unordered_map>

class Scene
{
private:

	std::unordered_map<std::string, Shape*> m_ShapesById;

	Camera* m_BindedCamera = nullptr;
public:

	void Render(const Camera& camera);

	void ShutDown();

	Shapes::Rectangle* CreateRectangle(const glm::vec2& halfExtent);

	Shapes::Circle* CreateCircle(float radius, float thickness);

	Shapes::Triangle* CreateTriangle(const glm::vec2 vertices[3]);

	bool RemoveShape(const std::string& id);

	void BindCamera(Camera* camera) { m_BindedCamera = camera; };

	Camera* GetBindedCamera() const { return m_BindedCamera; }
};