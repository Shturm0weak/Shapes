#include "Camera.h"

#include "Window.h"

#include "../../Vendor/glm/gtc/matrix_transform.hpp"

void Camera::Copy(const Camera& camera)
{
	m_ProjectionMat4 = camera.m_ProjectionMat4;
	m_ViewProjectionMat4 = camera.m_ViewProjectionMat4;
	m_Zoom = camera.m_Zoom;
	m_Transform = camera.m_Transform;
}

void Camera::UpdateViewProjection()
{
	m_ViewMat4 = glm::inverse(m_Transform.GetTransform());
	m_ViewProjectionMat4 = m_ProjectionMat4 * m_ViewMat4;
}

Camera::Camera()
{
	m_Transform.SetOnRotationCallback("Camera", std::bind(&Camera::UpdateViewProjection, this));
	m_Transform.SetOnTranslationCallback("Camera", std::bind(&Camera::UpdateViewProjection, this));
}

Camera::Camera(const Camera& camera)
{
	Copy(camera);
}

void Camera::operator=(const Camera& camera)
{
	Copy(camera);
}

glm::vec4 Camera::FromClipSpaceToScreenSpace(const glm::vec4& clipSpacePosition) const
{
	glm::vec4 screenSpacePosition = clipSpacePosition;

	screenSpacePosition /= screenSpacePosition.w;
	screenSpacePosition.x += 1.0f;
	screenSpacePosition.y += 1.0f;
	screenSpacePosition.x *= 0.5f * m_Size.x;
	screenSpacePosition.y *= 0.5f * m_Size.y;

	return screenSpacePosition;
}

void Camera::SetSize(const glm::vec2& size)
{
	m_Size = size;

	UpdateProjection();
}

void Camera::SetOrthographic(const glm::vec2& size)
{
	m_Size = size;
	const float ratio = GetAspect();
	m_ProjectionMat4 = glm::ortho(-ratio * m_Zoom, ratio * m_Zoom, -1.0f * m_Zoom,
		1.0f * m_Zoom, m_Znear, m_Zfar);

	UpdateViewProjection();
}

void Camera::UpdateProjection()
{
	SetOrthographic(m_Size);
}

void Camera::SetZoom(float zoom)
{
	m_Zoom = glm::clamp(zoom, 0.0f, 1000.f);
		
	UpdateProjection();
}

void Camera::SetZNear(float zNear)
{
	m_Znear = zNear;

	UpdateProjection();
}

void Camera::SetZFar(float zFar)
{
	m_Zfar = zFar;

	UpdateProjection();
}
