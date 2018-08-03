#include "engine.h"
#include "SDL_ttf.h"
#include "game.h"


int wmain(int argc, char* argv[])
{
	
	argc;
	argv;

	Engine engine;
	Game game(&engine);

	game.Initalize();
	while (game.Run()) game.Update();
	game.Shutdown();
	engine.Initialize();
	while (!engine.IsQuit())
	{
		engine.Update();
	}
	engine.Shutdown();

	return 0;
}