#pragma once

#include "Shape.h"

#include "../../Vendor/glm/glm.hpp"

namespace Shapes
{

	class Rectangle : public Shape
	{
	private:

		glm::vec2 m_HalfExtent = { 0, 0 };
	protected:

		virtual void Render(const Camera& camera) override;
	public:

		Rectangle(const glm::vec2& halfExtent);

		void SetHalfExtent(const glm::vec2& halfExtent) { m_HalfExtent = halfExtent; }

		glm::vec2 GetHalfExtent() const { return m_HalfExtent; }
	};

}
