#pragma once
#include <iostream>

using namespace std;

class Exception {
public:
	virtual void ShowError() = 0;
};

class FileNotFoundException : public Exception {
public:
	void ShowError() { cout << "Couldn't open files. Please, check if coordinates and highscore file name are correct and make sure files are in projects directory." << endl << endl; }
};
