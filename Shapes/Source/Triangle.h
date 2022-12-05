#pragma once

#include "Shape.h"

#include "../../Vendor/glm/glm.hpp"

namespace Shapes
{

	class Triangle : public Shape
	{
	private:

		glm::vec2 m_Vertices[3];
	protected:

		virtual void Render(const Camera& camera) override;
	public:

		Triangle(const glm::vec2 vertices[3]);

		void SetVertices(const glm::vec2 vertices[3]);

		glm::vec2 GetVertex(size_t i) const;
	};

}
