#pragma once

#include "../../Vendor/glm/glm.hpp"
#include "../../Vendor/glm/gtc/type_ptr.hpp"

namespace Utils
{

	inline glm::vec3 GetPosition(const glm::mat4& position)
	{
		const float* matPtr = glm::value_ptr(position);
		return { matPtr[12], matPtr[13], matPtr[14] };
	}

	inline glm::vec3 GetScale(const glm::mat4& scale)
	{
		const float* matPtr = glm::value_ptr(scale);
		return { matPtr[0], matPtr[5], matPtr[10] };
	}

};

