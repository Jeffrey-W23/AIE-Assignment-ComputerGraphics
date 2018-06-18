// includes, using, etc
#pragma once

// forward declares
struct GLFWwindow;

// namespace age for A Game Engine
namespace age {

	//--------------------------------------------------------------------------------------
	// Application object. The main application class.
	//--------------------------------------------------------------------------------------
	class Application
	{
	public:

		//--------------------------------------------------------------------------------------
		// Default Constructor.
		//--------------------------------------------------------------------------------------
		Application();

		//--------------------------------------------------------------------------------------
		// Default Destructor
		//--------------------------------------------------------------------------------------
		virtual ~Application();

		//--------------------------------------------------------------------------------------
		// Initialize: Set up the application, create a new window, call draw and update etc.
		//
		// Param: 
		//		kcTitle: The application window title. 
		//		nWidth: The width of the window.
		//		nHeight: The height of the window.
		// Return:
		//		bool: returns true if init is successful.
		//--------------------------------------------------------------------------------------
		bool Initialize(const char* kcTitle, int nWidth, int nHeight);

		//--------------------------------------------------------------------------------------
		// Start: Initialize the game.
		//
		// Returns:
		//		bool: Returns a true or false for if the startup is sucessful.
		//--------------------------------------------------------------------------------------
		virtual bool Start() = 0;

		//--------------------------------------------------------------------------------------
		// shutdown: Called on application shutdown and does all the cleaning up (eg. Deleteing pointers.)
		//--------------------------------------------------------------------------------------
		virtual void Shutdown() = 0;

		//--------------------------------------------------------------------------------------
		// Update: Updates objects over time.
		//
		// Param:
		//		deltaTime: Pass in deltaTime. A number that updates per second.
		//--------------------------------------------------------------------------------------
		virtual void Update(float deltaTime) = 0;

		//--------------------------------------------------------------------------------------
		// Draw: A virtual function to render (or "draw") objects to the screen.
		//--------------------------------------------------------------------------------------
		virtual void Draw() = 0;

		//--------------------------------------------------------------------------------------
		// Debug: Shows debug information in the console window.
		//--------------------------------------------------------------------------------------
		void Debug();

		//--------------------------------------------------------------------------------------
		// Quit: Sets the gameover bool and ends the main game loop and closes the application.
		//--------------------------------------------------------------------------------------
		void Quit() { m_bGameOver = true; }

		//--------------------------------------------------------------------------------------
		// GetWindowPtr: Access to the GLFW window
		//--------------------------------------------------------------------------------------
		GLFWwindow* GetWindowPtr() const { return m_pWindow; }

		//--------------------------------------------------------------------------------------
		// GetWindowWidth: Returns the width of the game window.
		//
		// Return:
		//		unsigned int: returns an int of the current game window width.
		//--------------------------------------------------------------------------------------
		unsigned int GetWindowWidth() const;
		
		//--------------------------------------------------------------------------------------
		// GetWindowHeight: Returns the height of the game window.
		//
		// Return:
		//		unsigned int: returns an int of the current game window height.
		//--------------------------------------------------------------------------------------
		unsigned int GetWindowHeight() const;

		//--------------------------------------------------------------------------------------
		// GetTime: returns time since application started
		//
		// Return:
		//		float: returns time in float value.
		//--------------------------------------------------------------------------------------
		float GetTime() const;

	protected:

		//--------------------------------------------------------------------------------------
		// NewWindow: Creates a new application window.
		//
		// Param: 
		//		kcTitle: The application window title. 
		//		nWidth: The width of the window.
		//		nHeight: The height of the window.
		// Return:
		//		bool: returns the success of the function.
		//--------------------------------------------------------------------------------------
		bool NewWindow(const char* kcTitle, int nWidth, int nHeight);

		//--------------------------------------------------------------------------------------
		// DestroyWindow: Destory the window on application shutdown.
		//--------------------------------------------------------------------------------------
		void DestroyWindow();

		//--------------------------------------------------------------------------------------
		// Pointer to the glfwindow
		//--------------------------------------------------------------------------------------
		GLFWwindow * m_pWindow;

		//--------------------------------------------------------------------------------------
		// Bool for the current state of the game.
		//--------------------------------------------------------------------------------------
		bool m_bGameOver;
	};
}