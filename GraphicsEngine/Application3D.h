// includes, using, etc
#pragma once
#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"
#include "Texture.h"

// forward declares
class FlyCamera;

//--------------------------------------------------------------------------------------
// Application3D object. Inherits from Application.
//--------------------------------------------------------------------------------------
class Application3D : public age::Application
{
public:

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Application3D();

	//--------------------------------------------------------------------------------------
	// Default Destructor.
	//--------------------------------------------------------------------------------------
	virtual ~Application3D();

	//--------------------------------------------------------------------------------------
	// Start: Initialize the game.
	//
	// Returns:
	//		bool: Returns a true or false for if the startup is sucessful.
	//--------------------------------------------------------------------------------------
	virtual bool Start();

	//--------------------------------------------------------------------------------------
	// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
	//--------------------------------------------------------------------------------------
	virtual void Shutdown();

	//--------------------------------------------------------------------------------------
	// Update: Updates objects over time.
	//
	// Param:
	//		deltaTime: Pass in deltaTime. A number that updates per second.
	//--------------------------------------------------------------------------------------
	virtual void Update(float deltaTime);

	//--------------------------------------------------------------------------------------
	// Draw: A virtual function to render (or "draw") objects to the screen.
	//--------------------------------------------------------------------------------------
	virtual void Draw();

protected:

	//--------------------------------------------------------------------------------------
	// A pointer to FlyCamera.
	//--------------------------------------------------------------------------------------
	FlyCamera* m_pCamera;

	//--------------------------------------------------------------------------------------
	// bool to unlock and lock camera
	//--------------------------------------------------------------------------------------
	bool m_bCameraLock;














	// PUT INTO DIFFERENT SEPERATE CLASSES
	// ------------ BUNNY ------------ // SORT
	aie::ShaderProgram m_bunnyShader;
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	// ------------ BUNNY ------------ // SORT

	// ------------ SPEAR ------------ // SORT
	aie::ShaderProgram m_spearShader;
	aie::OBJMesh m_spearMesh;
	glm::mat4 m_spearTransform;
	// ------------ SPEAR ------------ // SORT

	// ------------ PHONG ------------ // SORT
	aie::ShaderProgram m_phongShader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	// ------------ PHONG ------------ // SORT





	struct Light 
	{
		glm::vec3 direction;
	};

	Light m_light;






	// ------------ PLANETS ------------ // SORT
	//--------------------------------------------------------------------------------------
	// rotation matrix
	//--------------------------------------------------------------------------------------
	glm::mat4 rot;

	//--------------------------------------------------------------------------------------
	// parent matrix
	//--------------------------------------------------------------------------------------
	glm::mat4 parentMatrix;

	//--------------------------------------------------------------------------------------
	// child object
	//--------------------------------------------------------------------------------------
	glm::mat4 localMatrix;
	glm::mat4 globalMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	// ------------ PLANETS ------------ // SORT
	// PUT INTO DIFFERENT SEPERATE CLASSES
};