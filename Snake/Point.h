#pragma once

class Point {
private:
	int x, y;
	char symbol;

public:
	Point(int x = 0, int y = 0, char s = ' ') : x(x), y(y), symbol(s) {}
	Point(const Point& p) {
		x = p.x;
		y = p.y;
		symbol = p.symbol;
	}

	void setX(const int x) { this->x = x; }
	int getX() const { return x; }
	void setY(const int y) { this->y = y; }
	int getY() const { return y; }
	void set_XY(const int x, const int y) { this->x = x; this->y = y; }
	void setSymbol(const char s) { symbol = s; }
	char getSymbol() const { return symbol; }
	void setAll(const int x, const int y, const char s) { set_XY(x, y); setSymbol(s); }

	bool operator==(const Point& p2) const {
		return (this->x == p2.x && this->y == p2.y);
	}

	bool operator!=(const Point& p2) {
		return (this->x != p2.x || this->y != p2.y);
	}

	~Point() {}
};


