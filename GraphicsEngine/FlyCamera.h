// #includes, using, etc
#pragma once
#include "Camera.h"

// forward declares
struct GLFWwindow;

//--------------------------------------------------------------------------------------
// FlyCamera object.
//--------------------------------------------------------------------------------------
class FlyCamera : public Camera
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	FlyCamera();

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	~FlyCamera();

	//--------------------------------------------------------------------------------------
	// Update: A virtual function to update objects over time.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//		pGLWindow: pointer to the glfw window.
	//--------------------------------------------------------------------------------------
	virtual void Update(float deltaTime, GLFWwindow* pGLWindow);

protected:

	//--------------------------------------------------------------------------------------
	// A float for the camera movement speed.
	//--------------------------------------------------------------------------------------
	float m_fSpeed;

	//--------------------------------------------------------------------------------------
	// double values for camera mouse movement
	//--------------------------------------------------------------------------------------
	double m_dMouseX;
	double m_dMouseY;
	double m_dDeltaMouseX;
	double m_dDeltaMouseY;
};