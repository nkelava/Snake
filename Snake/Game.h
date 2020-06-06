#pragma once
#include <conio.h>
#include <windows.h>

#include "Player.h"
#include "Board.h"

#define SPEED 70
#define USERNAMELEN 12
#define FRUITPOINTS 3
#define LOGOSYMB 'X'
#define SNAKESYMB '*'
#define FRUITSYMB 'o'
#define CLRSCR system("cls")

enum movements { up = 72, left = 75, right = 77, down = 80 };

class Game : public Board, public Player {
private:
	Board board;
	vector<Point> snake;
	Point fruit;
	Player player;

	// SETTING
	void generateFruit();
	void ClearConsoleInputBuffer();
	void updateHighScores() const;
	// COMMANDS
	bool keyPressed();
	bool move(int);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	// CHECKING
	bool checkFruit();
	bool gameOver(const Point, const Point) const;
	//DISPLAY
	void EndScreen();

public:
	Game();
	//SCREENS
	string MenuScreen();
	void GameScreen();
	void HighScoreScreen();

	~Game();
};
