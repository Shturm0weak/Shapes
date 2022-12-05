#pragma once

#include "Transform.h"
#include "Camera.h"
#include "ID.h"

class Shape
{
private:

	ID m_Id;
protected:

	virtual void Render(const Camera& camera) = 0;
public:

	Transform m_Transform;
	glm::vec3 m_Color = { 0.0f, 0.0f, 1.0f };
	
	Shape() = default;
	virtual ~Shape() = default;

	std::string GetID() const { return m_Id.Get(); }

	friend class Scene;
};

