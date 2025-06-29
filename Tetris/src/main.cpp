#pragma region include system
#include <cstdlib>
#pragma endregion

#pragma region include project
#include "Game.hpp"
#pragma endregion

/// <summary>
/// main entry point
/// </summary>
/// <param name="argc">number of arguments</param>
/// <param name="argv">arguments array</param>
/// <returns>shutdown code</returns>
int main(int argc, char* argv[])
{
	// init playfield width and height
	int playfieldWidth = 16;
	int playfieldHeight = 32;

	// if any arguments are given
	if (argc > 1)
	{
		// set playfield width by argument 1
		playfieldWidth = atoi(argv[1]);

		// if more than 1 argument
		if (argc > 2)
			// set playfield height by argument 2
			playfieldHeight = atoi(argv[2]);
	}

	// create game and initialize
	Game game;
	game.Init(playfieldWidth, playfieldHeight);

	// game loop if game is running
	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}

	// shutdown correct
	return 0;
}