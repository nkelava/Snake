#include "Game.h"

using namespace std;

int main()
{
	Game game;
	string response;

	try {
		while ((response = game.MenuScreen()) == "HScore") {
			game.HighScoreScreen();
		}
		if (response == "Enter") {
			game.GameScreen();
		}
	}
	catch (FileNotFoundException error) {
		error.ShowError();
	}

	return 0;
}