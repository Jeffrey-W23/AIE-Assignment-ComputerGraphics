// includes, using, etc
#include "Application3D.h"
#include "Gizmos.h"
#include "FlyCamera.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
Application3D::Application3D()
{
	// Set defaults
	m_bCameraLock = false;
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Application3D::~Application3D()
{

}

//--------------------------------------------------------------------------------------
// Start:
//
// Return:
//--------------------------------------------------------------------------------------
bool Application3D::Start()
{
	// Create Aie gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);
	
	// initialize camera.
	m_pCamera = new FlyCamera();

	// create simple camera transforms
	m_pCamera->SetLookAt(glm::vec3(50), glm::vec3(0), glm::vec3(0, 1, 0)); //10
	m_pCamera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);









	// set the parent matrix
	parentMatrix = glm::mat4(1);
	parentMatrix[3] = glm::vec4(0, 0, 10, 1);

	// set the rotation matrix
	rot = glm::mat4(1);
	rot = glm::rotate(0.78553975f, glm::vec3(0, 1, 0));

	// apply rotation to the parentmatrix
	parentMatrix = rot * parentMatrix;

	// set the local matrix
	localMatrix = glm::mat4(1);
	localMatrix[3] = glm::vec4(0, 0, -2, 1);

	// apply local and parent to the global matrix
	globalMatrix = localMatrix * parentMatrix;









	// return success
	return true;
}

//--------------------------------------------------------------------------------------
// Shutdown:
//--------------------------------------------------------------------------------------
void Application3D::Shutdown()
{
	// clean up gizmo
	aie::Gizmos::destroy();

	// delete fly camera
	delete m_pCamera;
}

//--------------------------------------------------------------------------------------
// Update:
//
// Param:
//--------------------------------------------------------------------------------------
void Application3D::Update(float deltaTime)
{
	// clear gizmo buffer
	aie::Gizmos::clear();
	
	// Build grid 
	aie::Gizmos::addTransform(glm::mat4(1));
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	// loop through and create lines for grid
	for (int i = 0; i < 21; ++i)
	{
		// add lines
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}









	// update Rotation Matrix
	rot = glm::rotate(deltaTime, glm::vec3(0, 1, 0));

	// Parent Oribits Center
	parentMatrix = rot * parentMatrix;

	// parent spin
	rot = glm::rotate(deltaTime * 3, glm::vec3(0, 1, 0));
	parentMatrix = parentMatrix * rot;

	// Rotate child around parent
	rot = glm::rotate(deltaTime * -5, glm::vec3(1, 0, 0));
	localMatrix = rot * localMatrix;

	// spin child
	rot = glm::rotate(deltaTime * 5, glm::vec3(0, 1, 0));
	localMatrix = localMatrix * rot;

	// ... once child syncs. with parent.
	globalMatrix = parentMatrix * localMatrix;

	// Draw Shapes
	aie::Gizmos::addSphere(glm::vec3(0), 1, 4, 4, glm::vec4(1, 1, 0, 1), &parentMatrix);
	aie::Gizmos::addSphere(glm::vec3(0), 0.5f, 4, 4, glm::vec4(0, 1, 0, 1), &globalMatrix);









	// Unlock and lock the camera so that the mouse can be used to click imgui buttons
	if (glfwGetKey(GetWindowPtr(), GLFW_KEY_SPACE))
		m_bCameraLock = !m_bCameraLock;

	// if camera is not lock
	if (m_bCameraLock)
	{
		// Update the fly camera.
		m_pCamera->Update(deltaTime, GetWindowPtr());

		// Hide cursor
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	else if (!m_bCameraLock)
	{
		// Unhide cursor
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

//--------------------------------------------------------------------------------------
// Draw:
//--------------------------------------------------------------------------------------
void Application3D::Draw()
{
	// Draw the gizmo applied to camera
	aie::Gizmos::draw(m_pCamera->GetProjectionView());
}