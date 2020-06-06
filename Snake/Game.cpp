#include "Game.h"

Game::Game() {
	fruit.setSymbol(FRUITSYMB);
}

void Game::ClearConsoleInputBuffer() {
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}

string Game::MenuScreen() {
	board.setEmptyBoard();
	board.setScreenText("menuCoordinates.txt", LOGOSYMB);

	string nameTxt = "Enter name: ", exitTxt = "Press ESC to exit...", highScoreTxt = "Press TAB for highscores...";
	string name = "";
	int nameLen = nameTxt.length(), exitLen = exitTxt.length(), hsLen = highScoreTxt.length(), usernameLen;

	board.setTextLine(nameTxt, nameLen, 11, 4);
	board.setTextLine(highScoreTxt, hsLen, HEIGHT - 3, 1);
	board.setTextLine(exitTxt, exitLen, HEIGHT - 2, 1);

	char input;

	while (true) {
		CLRSCR;
		board.displayBoard();
		input = _getch();

		if (input == 27) { // Esc
			return "Esc";
		}
		else if (input == 13) { // Enter 
			if (name.empty() == false) {
				player.setName(name);
			}
			return "Enter";
		}
		else if (input == 9 || input == 11) { // Vertical and horizontal tab
			return "HScore";
		}
		else if (input == 8) {  // Backspace 
			if (name.empty() == false) {
				board.setSymbolAt(11, 16 + (name.length() - 1), ' ');
				name.pop_back();
			}
		}
		else {
			name.push_back(input);
			usernameLen = name.length();

			if (usernameLen <= USERNAMELEN) { // Limited username lenght because of window size
				board.setSymbolAt(11, 16 + (usernameLen - 1), name[usernameLen - 1]);
			}
		}
	}
}

void Game::HighScoreScreen() {
	board.setEmptyBoard();

	ifstream inFile;

	inFile.open("highscores.txt");

	if (!inFile) {
		inFile.close();
		throw FileNotFoundException();
	}

	string record, highScoreTxt = "TOP 5 HIGHSCORES";
	int pos = 1, recordLen, hsLen = highScoreTxt.length(), startRow = 7;

	board.setTextLine(highScoreTxt, hsLen, 4, 9);

	while (getline(inFile, record)) {
		record = to_string(pos) + "." + record;
		recordLen = record.length();

		board.setTextLine(record, recordLen, startRow, 9);

		++pos, ++startRow;
	}

	inFile.close();

	string exitTxt = "Press ESC to go to MENU...";
	int exitLen = exitTxt.length();

	board.setTextLine(exitTxt, exitLen, HEIGHT - 2, 1);

	CLRSCR;
	board.displayBoard();

	char input;

	while (true) {
		if ((input = _getch()) == 27) { break; }
	}
	Game::ClearConsoleInputBuffer();
}

void Game::updateHighScores() const {
	fstream ptrFile("highscores.txt");

	if (!ptrFile) {
		ptrFile.close();
		throw FileNotFoundException();
	}
	// Get players from file
	vector<Player> players;
	string playerName;
	int score;

	while (ptrFile >> playerName >> score) {
		Player fPlayer(playerName, score);
		players.push_back(fPlayer);
	}

	ptrFile.clear();
	ptrFile.seekg(0, ios::beg);
	// Add current player to vector od players than sort them in descending order
	if (players.empty() == true) {
		ptrFile << player.getName() << " " << to_string(player.getPoints()) << '\n';
	}
	else {
		players.push_back(player);
		sort(players.begin(), players.end(), greater<Player>());
		if (players.size() > 5) {  // We only need top 5 so when it reaches 6 delete last one
			players.pop_back();
		}

		for (vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
			ptrFile << it->getName() << " " << to_string(it->getPoints()) << '\n';
		}
	}
	ptrFile.close();
}

void Game::generateFruit() {
	fruit.set_XY(1 + rand() % (HEIGHT - 3), 1 + rand() % (WIDTH - 3));
	board.setSymbolAt(fruit);
}

void Game::GameScreen() {

	Point head(HEIGHT / 2, WIDTH / 2, SNAKESYMB);
	snake.push_back(head);

	board.setEmptyBoard();
	Game::generateFruit();

	int directionState = ::right, key;

	while (true) {
		board.setSnakeOnBoard(snake);
		CLRSCR;
		board.displayBoard();
		Sleep(SPEED);

		if (keyPressed()) {
			key = _getch();
			// Arrow keys have 2 ASCII values, 1. is 0 or 224 and it's same for all of them, 2. value differentiates them
			if (key == 0 || key == 224) {
				key = _getch(); // Because of 1 value we now need to catch the second one 
				if ((key == ::right && directionState != ::left) || (key == ::left && directionState != ::right)) {
					directionState = key;
				}
				if ((key == ::up && directionState != ::down) || (key == ::down && directionState != ::up)) {
					directionState = key;
				}
			}
			Game::ClearConsoleInputBuffer();
		}
		// If the place we want to move collide with the body, upgrade scores and exit the game
		if (move(directionState) == true) {
			updateHighScores();
			EndScreen();
			break;
		}

		if (checkFruit() == true) {
			Point p(fruit.getX(), fruit.getY(), SNAKESYMB);
			snake.push_back(p);
			player.addPoints(FRUITPOINTS);
			generateFruit();
		}
		cout << "\t\t\t SCORE: " << player.getPoints();
	}
}

bool Game::checkFruit() {
	return (snake.front() == fruit);
}

bool Game::keyPressed() {
	return _kbhit();
}

bool Game::move(int direction) {
	board.setSymbolAt(snake.back(), ' ');
	Point prevBack = snake.back();

	if (direction == ::up) {
		moveUp();
	}
	else if (direction == ::down) {
		moveDown();
	}
	else if (direction == ::left) {
		moveLeft();
	}
	else {
		moveRight();
	}
	// With moveX function tail is set to next position so we set tail to be head and pop that last redundant point
	snake.insert(snake.begin(), snake.back());
	snake.pop_back();

	return (gameOver(prevBack, snake.front()));
}

void Game::moveUp() {
	// Checking for borders
	if (snake.front().getX() == 1) {
		snake.back().set_XY(HEIGHT - 2, snake.front().getY());
	}
	else {
		snake.back().set_XY(snake.front().getX() - 1, snake.front().getY());
	}
}

void Game::moveDown() {
	if (snake.front().getX() == HEIGHT - 2) {
		snake.back().set_XY(1, snake.front().getY());
	}
	else {
		snake.back().set_XY(snake.front().getX() + 1, snake.front().getY());
	}
}

void Game::moveLeft() {
	if (snake.front().getY() == 1) {
		snake.back().set_XY(snake.front().getX(), WIDTH - 2);
	}
	else {
		snake.back().set_XY(snake.front().getX(), snake.front().getY() - 1);
	}
}

void Game::moveRight() {
	if (snake.front().getY() == WIDTH - 2) {
		snake.back().set_XY(snake.front().getX(), 1);
	}
	else {
		snake.back().set_XY(snake.front().getX(), snake.front().getY() + 1);
	}
}

bool Game::gameOver(const Point p1, const Point p2) const {
	return (p1 == p2 || find(snake.begin() + 1, snake.end(), snake.front()) != snake.end());
}

void Game::EndScreen() {
	board.setEmptyBoard();
	board.setScreenText("endCoordinates.txt", LOGOSYMB);

	string playerMsg = "Player: " + player.getName(), pointsMsg = "Points: " + to_string(player.getPoints());
	int playerMsgLen = playerMsg.length(), pointsMsgLen = pointsMsg.length();

	board.setTextLine(playerMsg, playerMsgLen, HEIGHT - 4, 5);
	board.setTextLine(pointsMsg, pointsMsgLen, HEIGHT - 3, 5);

	CLRSCR;
	board.displayBoard();
}

Game::~Game() {
}

