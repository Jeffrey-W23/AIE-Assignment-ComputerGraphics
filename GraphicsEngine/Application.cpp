// includes, using, etc
#include "Application.h"
#include <iostream>
#include <glm.hpp>
#include <ext.hpp>
#include "..//dependencies/glCore/gl_core_4_5.h"
#include "glfw3.h"
#include "Age.h"

// namespace age for A Game Engine
namespace age {

	//--------------------------------------------------------------------------------------
	// Default Constructor.
	//--------------------------------------------------------------------------------------
	Application::Application()
	{
		// set defaults
		m_pWindow = nullptr;
		m_bGameOver = false;
	}

	//--------------------------------------------------------------------------------------
	// Default Destructor
	//--------------------------------------------------------------------------------------
	Application::~Application()
	{

	}

	//--------------------------------------------------------------------------------------
	// NewWindow:
	//
	// Param:
	//
	// Return:
	//--------------------------------------------------------------------------------------
	bool Application::NewWindow(const char* kcTitle, int nWidth, int nHeight)
	{
		// if we can hook into the GPU
		if (glfwInit() == false)
		{
			// return false
			return false;
		}

		// Make a window with OpenGL render. Width, Height, Window Name, Screen pointer.
		m_pWindow = glfwCreateWindow(nWidth, nHeight, kcTitle, nullptr, nullptr);

		// check if window worked
		if (m_pWindow == nullptr)
		{
			// Clean up window and gpu linkage
			glfwTerminate();

			// -2 is a failure code
			return false;
		}

		// bring window to front
		glfwMakeContextCurrent(m_pWindow);

		// Before loading interface functions
		if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		{
			// Destory opengl window
			glfwDestroyWindow(m_pWindow);

			// Clean up window and gpu linkage
			glfwTerminate();

			// -3 is a failure code
			return false;
		}

		// Settings grey clear
		glClearColor(0.25f, 0.25f, 0.25f, 1);

		// enable depth
		glEnable(GL_DEPTH_TEST);

		// return true
		return true;
	}

	//--------------------------------------------------------------------------------------
	// DestroyWindow:
	//--------------------------------------------------------------------------------------
	void Application::DestroyWindow()
	{
		// Destory opengl window
		glfwDestroyWindow(m_pWindow);

		// Clean up window and gpu linkage
		glfwTerminate();
	}

	//--------------------------------------------------------------------------------------
	// Initialize:
	//
	// Param:
	//
	// Return:
	//--------------------------------------------------------------------------------------
	bool Application::Initialize(const char* kcTitle, int nWidth, int nHeight)
	{
		if (NewWindow(kcTitle, nWidth, nHeight) && Start())
		{
			// initialize vars for time
			age::clock m_cClock;
			age::time m_tStartTime = m_cClock.now();
			age::time m_tCurrentTime = m_cClock.now();
			age::time m_tPreviousTime = m_cClock.now();
			double deltaTime = 0;

			// run main game loop
			while (!m_bGameOver)
			{
				// calculate time
				m_tPreviousTime = m_tCurrentTime;
				m_tCurrentTime = m_cClock.now();
				auto Duration = m_tCurrentTime - m_tPreviousTime;
				deltaTime = Duration.count() * NANO_TO_SECONDS;

				// poll events
				glfwPollEvents();

				// update the game
				Run(float(deltaTime));

				// draw game graphics
				Render();

				// show debug information
				Debug();

				// clearing buffer - Colour and depth checks
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// swap the buffers for the window
				glfwSwapBuffers(m_pWindow);

				// close loop if the exit button or esc key is pressed
				if (glfwWindowShouldClose(m_pWindow) == false && glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS)
				{
					m_bGameOver = false;
				}
			}
		}

		// clean up
		Terminate();
		DestroyWindow();

		// Success
		return true;
	}

	//--------------------------------------------------------------------------------------
	// Debug:
	//--------------------------------------------------------------------------------------
	void Application::Debug()
	{
		// How many screens are connected to the gpu
		GLFWmonitor** ppScreens;
		int nCount = 0;
		ppScreens = glfwGetMonitors(&nCount);
		std::cout << "Monitor Count: " << nCount << std::endl;

		// Open Gl verison
		auto major = ogl_GetMajorVersion();
		auto minor = ogl_GetMinorVersion();
		printf("GL Version: %i.%i\n", major, minor);
	}
}