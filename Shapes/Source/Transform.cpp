#include "Transform.h"

#include "../../Vendor/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "../../Vendor/glm/gtx/quaternion.hpp"

#include "Utils.h"

void Transform::Copy(const Transform& transform)
{
	Translate(transform.GetPosition());
	Rotate(transform.GetRotation());
	Scale(transform.GetScale());

}

glm::vec3 Transform::GetPosition() const
{
	return Utils::GetPosition(m_PositionMat4);
}

glm::vec3 Transform::GetScale() const
{
	return Utils::GetScale(m_ScaleMat4);
}

void Transform::UpdateVectors()
{
	const float cosPitch = cos(m_Rotation.x);
	m_Back.z = cos(m_Rotation.y) * cosPitch;
	m_Back.x = sin(m_Rotation.y) * cosPitch;
	m_Back.y = sin(m_Rotation.x);
	m_Back = glm::normalize(m_Back);

	const glm::mat3 inverseTransform = m_InverseTransformMat3;
	m_Up = glm::normalize(glm::vec3(inverseTransform[0][1],
		inverseTransform[1][1], inverseTransform[2][1]));
}

void Transform::UpdateTransforms()
{
	m_TransformMat4 = m_PositionMat4 * m_RotationMat4 * m_ScaleMat4;
	m_InverseTransformMat3 = glm::inverse(m_TransformMat4);
}

void Transform::operator=(const Transform& transform)
{
	Copy(transform);
}

Transform::Transform(const Transform& transform)
{
	Copy(transform);
}

Transform::Transform(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
{
	Translate(position);
	Rotate(rotation);
	Scale(scale);
}

void Transform::Translate(const glm::vec3& position)
{
	m_PreviousPosition = GetPosition();
	m_PositionDelta = position - m_PreviousPosition;
	m_PositionMat4 = glm::translate(glm::mat4(1.0f), position);

	UpdateTransforms();

	for (auto& onTranslationCallback : m_OnTranslationCallbacks)
	{
		onTranslationCallback.second();
	}
}

void Transform::Rotate(const glm::vec3& rotation)
{
	m_PreviousRotation = m_Rotation;
	m_Rotation = rotation;
	m_RotationDelta = m_Rotation - m_PreviousRotation;
	m_RotationMat4 = glm::toMat4(glm::quat(m_Rotation));

	UpdateTransforms();
	UpdateVectors();

	for (auto& onRotationCallback : m_OnRotationCallbacks)
	{
		onRotationCallback.second();
	}
}

void Transform::Scale(const glm::vec3& scale)
{
	m_PreviousScale = GetScale();
	m_ScaleDelta = scale - m_PreviousScale;
	m_ScaleMat4 = glm::scale(glm::mat4(1.0f), scale);

	UpdateTransforms();

	for (auto& onScaleCallback : m_OnScaleCallbacks)
	{
		onScaleCallback.second();
	}
}

void Transform::RemoveOnRotationCallback(const std::string& label)
{
	auto callback = m_OnRotationCallbacks.find(label);
	if (callback != m_OnRotationCallbacks.end())
	{
		m_OnRotationCallbacks.erase(callback);
	}
}

void Transform::RemoveOnTranslationCallback(const std::string& label)
{
	auto callback = m_OnTranslationCallbacks.find(label);
	if (callback != m_OnTranslationCallbacks.end())
	{
		m_OnTranslationCallbacks.erase(callback);
	}
}

void Transform::RemoveOnScaleCallback(const std::string& label)
{
	auto callback = m_OnScaleCallbacks.find(label);
	if (callback != m_OnScaleCallbacks.end())
	{
		m_OnScaleCallbacks.erase(callback);
	}
}