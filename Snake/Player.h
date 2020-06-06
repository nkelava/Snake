#pragma once

#include <string>

using namespace std;

class Player {
private:
	string userName;
	int points;

public:
	Player(string name = "Unknown", int pts = 0) : userName(name), points(pts) {};

	void setName(const string name) { userName = name; }
	string getName() const { return userName; }
	int getNameLenght() const { return userName.length(); }
	char getNameLetterAt(const int i) const { return userName[i]; };
	void addPoints(const int p) { points += p; }
	int getPoints() const { return points; }
	void setPoints(const int p) { points = p; }

	bool operator<(const Player& p2) const
	{
		return (this->points < p2.points);
	}

	bool operator>(const Player& p2) const
	{
		return (this->points > p2.points);
	}

	~Player() {};
};

