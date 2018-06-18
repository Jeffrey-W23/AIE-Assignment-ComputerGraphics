// includes, using, etc
#include "Application3D.h"
#include "Gizmos.h"
#include "FlyCamera.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"

//--------------------------------------------------------------------------------------
// Default Constructor.
//--------------------------------------------------------------------------------------
Application3D::Application3D()
{
	// Set defaults
	m_bCameraLock = false;

	






	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };
}

//--------------------------------------------------------------------------------------
// Default Destructor
//--------------------------------------------------------------------------------------
Application3D::~Application3D()
{

}

//--------------------------------------------------------------------------------------
// Start: Initialize the game.
//
// Returns:
//		bool: Returns a true or false for if the startup is sucessful.
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














	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");
	

	if (m_normalMapShader.link() == false)
	{
		printf("Shader Error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

	if (m_spearMesh.load("../models/soulspear/soulspear.obj", true, true) == false) {
		printf("Bunny Mesh Error!\n");
		return false;
	}

	m_spearTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};


















	// ------------ PLANETS ------------ // SORT
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
	// ------------ PLANETS ------------ // SORT













	// return success
	return true;
}

//--------------------------------------------------------------------------------------
// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
//--------------------------------------------------------------------------------------
void Application3D::Shutdown()
{
	// clean up gizmo
	aie::Gizmos::destroy();

	// delete fly camera
	delete m_pCamera;
}

//--------------------------------------------------------------------------------------
// Update: Updates objects over time.
//
// Param:
//		deltaTime: Pass in deltaTime. A number that updates per second.
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

	// ------------ PLANETS ------------ // SORT
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
	// ------------ PLANETS ------------ // SORT












	// query time since application started
	float time = GetTime();

	// rotate the light
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));









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
// Draw: A virtual function to render (or "draw") objects to the screen.
//--------------------------------------------------------------------------------------
void Application3D::Draw()
{









	// bind phong shader program
	m_normalMapShader.bind();
		// bind light
	m_normalMapShader.bindUniform("Ia", m_ambientLight);
	m_normalMapShader.bindUniform("Id", m_light.diffuse);
	m_normalMapShader.bindUniform("Is", m_light.specular);
	m_normalMapShader.bindUniform("LightDirection", m_light.direction);







	
	
	// bind transform
	auto pvm = m_pCamera->GetProjectionView() *  m_spearTransform;




	
	
	


	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	




	// bind transforms for lighting
	m_normalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_spearTransform)));

	//  send the camera�s position to the shader as a uniform:
	m_normalMapShader.bindUniform("cameraPosition", m_pCamera->GetPosition());

	// draw bunny mesh
	m_spearMesh.draw();








	// Draw the gizmo applied to camera
	aie::Gizmos::draw(m_pCamera->GetProjectionView());
}