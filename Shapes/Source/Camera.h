#pragma once

#include "Transform.h"

class Camera
{
private:

	glm::mat4 m_ViewMat4;
	glm::mat4 m_ProjectionMat4;
	glm::mat4 m_ViewProjectionMat4;
		
	glm::vec2 m_Size;

	float m_Zoom = 1.0f;
	float m_Znear = 0.1f;
	float m_Zfar = 1000.0f;

	void Copy(const Camera& camera);
		
	void UpdateViewProjection();
public:

	Camera();
	Camera(const Camera& camera);
	void operator=(const Camera& camera);

	Transform m_Transform;
		
	glm::mat4 GetViewProjectionMat4() const { return m_ViewProjectionMat4; }
		
	glm::mat4 GetProjectionMat4() const { return m_ProjectionMat4; }
		
	glm::mat4 GetViewMat4() const { return m_ViewMat4; }

	glm::vec2 GetSize() const { return m_Size; }

	glm::vec4 FromClipSpaceToScreenSpace(const glm::vec4& clipSpacePosition) const;

	void SetSize(const glm::vec2& size);

	float GetPitch() const { return m_Transform.GetRotation().x; }
		
	float GetYaw() const { return m_Transform.GetRotation().y; }
		
	float GetRoll() const { return m_Transform.GetRotation().z; }
		
	void SetOrthographic(const glm::vec2& size);

	void UpdateProjection();
		
	void SetZoom(float zoom);
		
	float GetZoom() const { return m_Zoom; }
		
	float GetAspect() const { return m_Size.x / m_Size.y; }
		
	float GetZNear() const { return m_Znear; }

	void SetZNear(float zNear);

	float GetZFar() const { return m_Zfar; }
		
	void SetZFar(float zFar);
};