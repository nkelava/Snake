#include "Board.h"

Board::Board() {
	srand(time(NULL));

	board = new char* [HEIGHT];
	for (unsigned int i = 0; i < HEIGHT; ++i) { board[i] = new char[WIDTH]; }
}

void Board::displayBoard() const {
	for (unsigned int i = 0; i < HEIGHT; ++i) {
		for (unsigned int j = 0; j < WIDTH - 1; ++j) {
			cout << board[i][j] << " ";
		}
		cout << board[i][WIDTH - 1] << endl;
	}
}

void Board::setEmptyBoard() {
	for (unsigned int i = 0; i < HEIGHT; ++i) {
		for (unsigned int j = 0; j < WIDTH; ++j) {
			board[i][j] = (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) ? FRAMESYMB : ' ';
		}
	}
}

void Board::setSymbolAt(const Point p, const char symbol) {
	board[p.getX()][p.getY()] = symbol;
}

void  Board::setSymbolAt(const Point p) {
	board[p.getX()][p.getY()] = p.getSymbol();
}

void  Board::setSymbolAt(const int x, const int y, char symbol) {
	board[x][y] = symbol;
}

void Board::setTextLine(string text, int textLength, int startRow, int startCol) {
	for (unsigned int i = 0; i < textLength; ++i) {
		board[startRow][i + startCol] = text[i];
	}
}

void Board::setScreenText(string file, char symb) {
	int x1, y1, x2, y2;
	ifstream inFile(file);

	if (!inFile) {
		inFile.close();
		throw FileNotFoundException();
	}

	while (inFile >> x1 >> y1 >> x2 >> y2) {
		draw_line(x1, y1, x2, y2, symb);
	}

	inFile.close();
}

void Board::setSnakeOnBoard(vector<Point> snake) {
	for (vector<Point>::const_iterator it = snake.begin(); it != snake.end(); ++it) {
		board[it->getX()][it->getY()] = it->getSymbol();
	}
}

void Board::draw(int c1, int c1xy, int c2, char ch, const directions dir, const angles angl) {
	if (angl == verthor) {
		while (c1 != c2) {
			(dir == updown) ? draw_char(c1, c1xy, ch) : draw_char(c1xy, c1, ch);
			(c1 > c2) ? --c1 : ++c1; // Incr/decr depeneding on other cooridinate(inconstant) position(lower/higher)
		}
		(dir == updown) ? draw_char(c1, c1xy, ch) : draw_char(c1xy, c1, ch);
	}
	else {
		while (c1 != c2) {
			draw_char(c1, c1xy, ch);
			if (dir == brtl) {   // Bottom-right to top-left or vice versa direction
				(c1 > c2) ? --c1xy : ++c1xy;
			}
			else {	// Bottom-left to top-right or vice versa direction
				(c1 > c2) ? ++c1xy : --c1xy;
			}
			(c1 > c2) ? --c1 : ++c1;
		}
		draw_char(c1, c1xy, ch);
	}
}

void Board::draw_char(int x, int y, char ch) {
	board[x][y] = ch;
}

void Board::draw_line(const int x1, const int y1, const int x2, const int y2, const char ch) {
	if (y1 == y2) { draw(x1, y1, x2, ch, updown, verthor); }  // 1 indicates it's up or down direction(v-h)/bottom-right to top-left and vice versa(d) 
	else if (x1 == x2) { draw(y1, x1, y2, ch, leftright, verthor); }  // 2(can be any other than 1) for left or right direction(v-h)/bottom-left to top-right and vice versa(d)
	else {
		if (check_diagonal(x1, y1, x2, y2)) {  // Checks possibility of drawing diagonal
			directions dir = (check_direction(x1, y1, x2, y2)) ? brtl : bltr;
			draw(x1, y1, x2, ch, dir, diagonal);
		}
		else { cout << "Couldn't draw one diagonal line. Please make sure points are diagonal." << endl; }
	}
}

bool Board::check_diagonal(int x1, int y1, int x2, int y2) const {
	directions dir = (check_direction(x1, y1, x2, y2)) ? brtl : bltr; // Get direction so we know which way to go

	while (x1 != x2) {  // Go from one point diagonally untill you reach other point
		if (dir == brtl) {   // Go in direction br-tl or vice verse 
			(x1 > x2) ? --y1 : ++y1;
		}
		else {
			(x1 > x2) ? ++y1 : --y1; // Go bl-tr or vice versa
		}
		(x1 > x2) ? --x1 : ++x1;
	}
	return (y1 == y2) ? true : false;
}

bool Board::check_direction(const int x1, const int y1, const int x2, const int y2) const {
	return ((x1 > x2 && y1 > y2) || (x1 < x2 && y1 < y2)); // Checks for br-tl, if it returns false we know it's bl-tr
}

Board::~Board() {
	for (unsigned int i = 0; i < HEIGHT; ++i) {
		delete[] board[i];
	}
	delete[] board;
}

