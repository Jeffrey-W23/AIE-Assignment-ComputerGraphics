// includes, using, etc
#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include "..//dependencies/glCore/gl_core_4_5.h"
#include "glfw3.h"
#include "Gizmos.h"

//--------------------------------------------------------------------------------------
// main: the main function of the project.
//--------------------------------------------------------------------------------------
int main()
{
	// if we can hook into the GPU
	if (glfwInit() == false)
	{
		// -1 is a failure code
		return -1;
	}

	// How many screens are connected to the gpu
	GLFWmonitor** screens;
	int count = 0;
	screens = glfwGetMonitors(&count);
	std::cout << count << std::endl;

	// Make a window with OpenGL render. Width, Height, Window Name, Screen pointer.
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	
	// check if window worked
	if (window == nullptr) 
	{
		// Clean up window and gpu linkage
		glfwTerminate();
		
		// -2 is a failure code
		return -2;
	}

	// bring window to front
	glfwMakeContextCurrent(window);

	// Before loading interface functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// Destory opengl window
		glfwDestroyWindow(window);

		// Clean up window and gpu linkage
		glfwTerminate();

		// -3 is a failure code
		return -3;
	}

	// Open Gl verison
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// Settings grey clear
	glClearColor(0.25f, 0.25f, 0.25f, 1);

	// enable depth
	glEnable(GL_DEPTH_TEST);

	// Create Aie gizmos -- TODO better numbers
	aie::Gizmos::create(10000, 10000, 10000, 10000);
	
	// create a new view matrix and projection matrix. View is the lense of the camera, projection being the feild of view.
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	// while the application is open
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{
		// clearing buffer - Colour and depth checks
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		aie::Gizmos::addAABBFilled(glm::vec3(-2.0f,0.0f,0.0f), glm::vec3(1.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		// Draw the gizmo applied to camera
		aie::Gizmos::draw(projection * view);

		// swap the buffers for the window
		glfwSwapBuffers(window);
		
		//  poll events
		glfwPollEvents();
	}

	// clean up gizmo
	aie::Gizmos::destroy();

	// Destory opengl window
	glfwDestroyWindow(window);

	// Clean up window and gpu linkage
	glfwTerminate();

	return 0;
}