// #includes, using, etc
#include "Camera.h"

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
Camera::Camera()
{
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Camera::~Camera()
{
}

//--------------------------------------------------------------------------------------
// SetPerspective: Create perspective projection transform.
//
// Param:
//		fFieldOfView: float value for the field of view of the camera.
//		fAspectRatio: float value for the aspect ratio of the camera.
//		fNear: float value for perspective near value.
//		fFar: float value for perspective far value.
//--------------------------------------------------------------------------------------
void Camera::SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar)
{
	// create perspective transform
	m_m4ProjectionTransform = glm::perspective(fFieldOfView, fAspectRatio, fNear, fFar);
	
	// update transfrom
	UpdateProjectionViewTransform();
}

//--------------------------------------------------------------------------------------
// SetLookAt: Builds the view transform.
//
// Param:
//		v3From: vector3 value for from where to look at.
//		v3To: vector3 value for where to look at.
//		v3Up: vector3 value for up.
//--------------------------------------------------------------------------------------
void Camera::SetLookAt(glm::vec3 v3From, glm::vec3 v3To, glm::vec3 v3Up)
{
	// build the transform
	m_m4ViewTransform = glm::lookAt(v3From, v3To, v3Up);
	m_m4WorldTransform = glm::inverse(m_m4ViewTransform);
	
	// update transform
	UpdateProjectionViewTransform();
}

//--------------------------------------------------------------------------------------
// SetPosition: Set the position of the camera in 3d space.
//
// Param:
//		v3Position: a vector3 for the desired position of the camera.
//--------------------------------------------------------------------------------------
void Camera::SetPosition(glm::vec3 v3Position)
{
	// set the position vector
	m_m4WorldTransform[3] = glm::vec4(v3Position.x, v3Position.y, v3Position.z, 1);
	m_m4ViewTransform = glm::inverse(m_m4WorldTransform);
	
	// update transform
	UpdateProjectionViewTransform();
}

//--------------------------------------------------------------------------------------
// UpdateProjectionViewTransform: Update the projection view transform.
//--------------------------------------------------------------------------------------
void Camera::UpdateProjectionViewTransform()
{
	m_m4ProjectionViewTransform = m_m4ProjectionTransform * m_m4ViewTransform;
}