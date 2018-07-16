#include "engine.h"
#include "SDL_ttf.h"


int wmain(int argc, char* argv[])
{
	argc;
	argv;


	Engine engine;

	engine.Initialize();
	while (!engine.IsQuit())
	{
		engine.Update();
	}
	engine.Shutdown();

	return 0;
}