// includes, using, etc
#include <crtdbg.h>
#include "Application3D.h"

//--------------------------------------------------------------------------------------
// main: the main function of the project.
//--------------------------------------------------------------------------------------
int main()
{
	// Memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// new application pointer
	auto app = new Application3D();

	// Initialize
	app->Initialize("Age", 1280, 720);

	// delete app
	delete app;

	// return
	return 0;
}