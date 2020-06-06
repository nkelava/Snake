#pragma once

#include <algorithm>
#include <fstream>
#include <ctime>
#include <vector>
#include <iterator>

#include "Point.h"
#include "Error.h"

#define HEIGHT 18
#define WIDTH 33
#define FRAMESYMB 'X'

#define CLRSCR system("cls")

enum angles { verthor, diagonal }; // verthor - vertical/horizontal
enum directions { updown, leftright, brtl, bltr }; // brtl(bottom-right top-left), bltr(bottom-left top-right)

class Board : public Point {
private:
	char** board;

public:
	Board();

	// DISPLAY
	void displayBoard() const;
	// SETTING
	void setEmptyBoard();
	void setSymbolAt(const Point, const char);
	void setSymbolAt(const Point);
	void setSymbolAt(const int, const int, char);
	void setTextLine(string, int, int, int);
	void setScreenText(string, char);
	void setSnakeOnBoard(vector<Point>);
	void draw(int, int, int, char, const directions, const angles);
	void draw_char(int, int, char);
	void draw_line(const int, const int, const int, const int, const char);
	// CHECKING
	bool check_diagonal(int, int, int, int) const;
	bool check_direction(const int, const int, const int, const int) const;

	~Board();
};
