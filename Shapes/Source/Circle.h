#pragma once

#include "Shape.h"

#include "../../Vendor/glm/glm.hpp"

namespace Shapes
{

	class Circle : public Shape
	{
	private:

		float m_Radius;
		float m_Thickness;
	protected:

		virtual void Render(const Camera& camera) override;
	public:

		Circle(float radius, float thickness);

		void SetRadius(float radius) { m_Radius = radius; }

		float GetRadius() const { return m_Radius; }

		void SetThickness(float thickness) { m_Thickness = thickness; }

		float GetThickness() const { return m_Thickness; }
	};

}
