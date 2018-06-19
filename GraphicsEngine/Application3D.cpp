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

	// initialize light
	m_lMovingLight.m_v3Diffuse = { 1, 1, 0 };
	m_lMovingLight.m_v3Specular = { 1, 1, 0 };
	m_v3AmbientLight = { 0.25f, 0.25f, 0.25f };
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

	//-------- LOAD SHADERS --------//
	// load normalmap shader
	m_sNormalMapShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	m_sNormalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	// if the linking fails
	if (m_sNormalMapShader.link() == false)
	{
		// print error and return false
		printf("Shader Error: %s\n", m_sNormalMapShader.getLastError());
		return false;
	}

	// load phong shader
	m_sPhongShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/phong.vert");
	m_sPhongShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/phong.frag");
	
	// if the linking fails
	if (m_sPhongShader.link() == false)
	{
		// print error and return false
		printf("Shader Error: %s\n", m_sPhongShader.getLastError());
		return false;
	}

	// load unlit shader
	m_sUnlitShader.loadShader(aie::eShaderStage::VERTEX, "../shaders/unlit.vert");
	m_sUnlitShader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/unlit.frag");

	// if the linking fails
	if (m_sUnlitShader.link() == false)
	{
		// print error and return false
		printf("Shader Error: %s\n", m_sUnlitShader.getLastError());
		return false;
	}
	//-------- LOAD SHADERS --------//

	//-------- LOAD MODELS --------//
	// load the spear model
	if (m_mSpearMesh.load("../models/soulspear/soulspear.obj", true, true) == false) {
		
		// print error and return false
		printf("Spear Mesh Error!\n");
		return false;
	}

	// set the spear model trasform.
	m_m4SpearTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		-5,0,-5,1
	};

	// load the Bunny model
	if (m_mBunnyMesh.load("../models/stanford/Bunny.obj", true, true) == false) {
		
		// print error and return false
		printf("Bunny Mesh Error!\n");
		return false;
	}

	// set the bunny model trasform.
	m_m4BunnyTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

	// load the rock model
	if (m_mRockMesh.load("../models/Rock/Rock.obj", true, true) == false) {
		
		// print error and return false
		printf("Rock Mesh Error!\n");
		return false;
	}
	
	// set the rock model trasform.
	m_m4RockTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		5,0,-2,1
	};

	// load the Sandbag model
	if (m_mSandbagMesh.load("../models/Sandbag/Sandbag.obj", true, true) == false) {

		// print error and return false
		printf("Sandbag Mesh Error!\n");
		return false;
	}

	// set the Sandbag model trasform.
	m_m4SandbagTransform = {
		0.01f,0,0,0,
		0,0.01f,0,0,
		0,0,0.01f,0,
		5,0,0,1.0f
	};

	// load the skullmountain model
	if (m_mSkullMountainMesh.load("../models/skullmountain/Skull_Mountain.obj", true, true) == false) {

		// print error and return false
		printf("Sandbag Mesh Error!\n");
		return false;
	}

	// set the skullmountain model trasform.
	m_m4SkullMountainTransform = {
		0.01f,0,0,0,
		0,0.01f,0,0,
		0,0,0.01f,0,
		5,0,6,1.0f
	};
	//-------- LOAD MODELS --------//

















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

	// query time since application started
	float time = GetTime();

	// rotate the light
	m_lMovingLight.m_v3Direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));














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
	//---- NORMALMAP SHADER WITH SPEAR ----//
	// bind normalmap shader program
	m_sNormalMapShader.bind();
	
	// bind lighting
	m_sNormalMapShader.bindUniform("Ia", m_v3AmbientLight);
	m_sNormalMapShader.bindUniform("Id", m_lMovingLight.m_v3Diffuse);
	m_sNormalMapShader.bindUniform("Is", m_lMovingLight.m_v3Specular);
	m_sNormalMapShader.bindUniform("LightDirection", m_lMovingLight.m_v3Direction);

	// bind camera transform
	auto SpearPVM = m_pCamera->GetProjectionView() *  m_m4SpearTransform;
	m_sNormalMapShader.bindUniform("ProjectionViewModel", SpearPVM);
	
	// bind transforms for lighting the spear
	m_sNormalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_m4SpearTransform)));

	// Send the camera’s position to the shader as a uniform:
	m_sNormalMapShader.bindUniform("cameraPosition", m_pCamera->GetPosition());

	// draw spear mesh
	m_mSpearMesh.draw();

	// bind camera transform
	auto SandbagPVM = m_pCamera->GetProjectionView() *  m_m4SandbagTransform;
	m_sNormalMapShader.bindUniform("ProjectionViewModel", SandbagPVM);

	// bind transforms for lighting the sandbag
	m_sNormalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_m4SandbagTransform)));

	// draw sandbag mesh
	m_mSandbagMesh.draw();

	// bind camera transform
	auto SkullMountainPVM = m_pCamera->GetProjectionView() *  m_m4SkullMountainTransform;
	m_sNormalMapShader.bindUniform("ProjectionViewModel", SkullMountainPVM);

	// bind transforms for lighting the skullmountain
	m_sNormalMapShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_m4SkullMountainTransform)));

	// draw skullmountain mesh
	m_mSkullMountainMesh.draw();
	//---- NORMALMAP SHADER WITH SPEAR ----//

	//---- PHONG SHADER WITH BUNNY ----//
	// bind phong shader
	m_sPhongShader.bind();

	// bind lighting
	m_sPhongShader.bindUniform("Ia", m_v3AmbientLight);
	m_sPhongShader.bindUniform("Id", m_lMovingLight.m_v3Diffuse);
	m_sPhongShader.bindUniform("Is", m_lMovingLight.m_v3Specular);
	m_sPhongShader.bindUniform("LightDirection", m_lMovingLight.m_v3Direction);

	// bind camera transform
	auto PhongPVM = m_pCamera->GetProjectionView() *  m_m4BunnyTransform;
	m_sPhongShader.bindUniform("ProjectionViewModel", PhongPVM);

	// bind transforms for lighting
	m_sPhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_m4BunnyTransform)));

	// Send the camera’s position to the shader as a uniform:
	m_sPhongShader.bindUniform("cameraPosition", m_pCamera->GetPosition());

	// draw Bunny mesh
	m_mBunnyMesh.draw();
	//---- PHONG SHADER WITH BUNNY ----//

	//---- UNLIT SHADER WITH ROCK ----//
	// bind unlit shader
	m_sUnlitShader.bind();

	// bind camera transform
	auto UnlitPVM = m_pCamera->GetProjectionView() *  m_m4RockTransform;
	m_sUnlitShader.bindUniform("ProjectionViewModel", UnlitPVM);

	// draw rock mesh
	m_mRockMesh.draw();
	//---- UNLIT SHADER WITH ROCK ----//

	// Draw the gizmo applied to camera
	aie::Gizmos::draw(m_pCamera->GetProjectionView());
}