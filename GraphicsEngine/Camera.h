// #includes, using, etc
#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// forward declares
struct GLFWwindow;

//--------------------------------------------------------------------------------------
// Camera object.
//--------------------------------------------------------------------------------------
class Camera
{
public:
	
	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Camera();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~Camera();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects over time.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//		pGLWindow: pointer to the glfw window.
	//--------------------------------------------------------------------------------------
	virtual void Update(float deltaTime, GLFWwindow* pGLWindow) = 0;
	
	//--------------------------------------------------------------------------------------
	// SetPerspective: 
	//
	// Param:
	//		fFieldOfView: float value for the field of view of the camera.
	//		fAspectRatio: float value for the aspect ratio of the camera.
	//		fNear: float value for perspective near value.
	//		fFar: float value for perspective far value.
	//--------------------------------------------------------------------------------------
	void SetPerspective(float fFieldOfView, float fAspectRatio, float fNear, float fFar);

	//--------------------------------------------------------------------------------------
	// SetLookAt: Builds the view transform.
	//
	// Param:
	//		v3From: vector3 value for from where to look at.
	//		v3To: vector3 value for where to look at.
	//		v3Up: vector3 value for up.
	//--------------------------------------------------------------------------------------
	void SetLookAt(glm::vec3 v3From, glm::vec3 v3To, glm::vec3 v3Up);

	//--------------------------------------------------------------------------------------
	// SetPosition: Set the position of the camera in 3d space.
	//
	// Param:
	//		v3Position: a vector3 for the desired position of the camera.
	//--------------------------------------------------------------------------------------
	void SetPosition(glm::vec3 v3Position);

	//--------------------------------------------------------------------------------------
	// GetPosition: Get the position of the camera in 3d space.
	//
	// Return:
	//		vec3: a vector3 for the current position of the camera.
	//--------------------------------------------------------------------------------------
	glm::vec3 GetPosition();

	//--------------------------------------------------------------------------------------
	// UpdateProjectionViewTransform: 
	//--------------------------------------------------------------------------------------
	void UpdateProjectionViewTransform();

	//--------------------------------------------------------------------------------------
	// GetWorldTransform: Get the world transform for the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the world transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetWorldTransform() { return m_m4WorldTransform; };

	//--------------------------------------------------------------------------------------
	// GetView: Get the viewTransform of the camera
	//
	// Return:
	//		mat4: Matrix4 value of the viewTransform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetView() { return m_m4ViewTransform; };

	//--------------------------------------------------------------------------------------
	// GetProjection: Get the projection transfrom of the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the projection transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetProjection() { return m_m4ProjectionTransform; };

	//--------------------------------------------------------------------------------------
	// GetProjectionView: Get the projection view transform of the camera.
	//
	// Return:
	//		mat4: Matrix4 value of the projection view transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 GetProjectionView() { return m_m4ProjectionViewTransform; };

protected:

	//--------------------------------------------------------------------------------------
	// A matrix4 for the World Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4WorldTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the ViewTransform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ViewTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the Projection Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ProjectionTransform;

	//--------------------------------------------------------------------------------------
	// A matrix4 for the Projection View Transform.
	//--------------------------------------------------------------------------------------
	glm::mat4 m_m4ProjectionViewTransform;
};