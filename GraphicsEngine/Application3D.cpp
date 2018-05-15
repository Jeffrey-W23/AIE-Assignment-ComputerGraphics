// includes, using, etc
#include "Application3D.h"
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
Application3D::Application3D()
{

}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Application3D::~Application3D()
{

}

//--------------------------------------------------------------------------------------
// NewWindow:
//
// Return:
//--------------------------------------------------------------------------------------
bool Application3D::Start()
{
	// Create Aie gizmos
	aie::Gizmos::create(10000, 10000, 10000, 10000);
	
	parentMatrix = glm::mat4(1);
	parentMatrix[3] = glm::vec4(0, 0, 10, 1);

	glm::mat4 rot(1);
	rot = glm::rotate(0.78553975f, glm::vec3(0, 1, 0));

	parentMatrix = rot * parentMatrix;

	localMatrix[3] = glm::vec4(0, 0, -2, 1);

	globalMatrix = localMatrix * parentMatrix;

	// create a new view matrix and projection matrix. View is the lense of the camera, projection being the feild of view.
	viewMatrix = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	// return success
	return true;
}

//--------------------------------------------------------------------------------------
// Terminate:
//--------------------------------------------------------------------------------------
void Application3D::Terminate()
{
	// clean up gizmo
	aie::Gizmos::destroy();
}

//--------------------------------------------------------------------------------------
// Run:
//
// Param:
//--------------------------------------------------------------------------------------
void Application3D::Run(float deltaTime)
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

	// create a red aabb
	aie::Gizmos::addAABBFilled(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(1.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	// Create Rotation Matrix
	glm::mat4 rot(1);
	rot = glm::rotate(deltaTime, glm::vec3(0, 1, 0));

	// Apply rotation to parent
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


	aie::Gizmos::addSphere(glm::vec3(0), 1, 4, 4, glm::vec4(1, 1, 0, 1), &parentMatrix);
	aie::Gizmos::addSphere(glm::vec3(0), 0.5f, 4, 4, glm::vec4(1, 0, 0, 1), &globalMatrix);
}

//--------------------------------------------------------------------------------------
// Render:
//--------------------------------------------------------------------------------------
void Application3D::Render()
{
	// Draw the gizmo applied to camera
	aie::Gizmos::draw(projectionMatrix * viewMatrix);
}