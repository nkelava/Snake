# Snake

For my OOP class project I had to make an ASCII console game, so I chose one of the best old school classic games, (dramatic pause) Snake :D For the people who never played snake before here's a link with little more information about the game: https://en.wikipedia.org/wiki/Snake_(video_game_genre).

When player starts the game, Main menu shows up and there are 3 options:
                   
                   1. Player can either press ESC and exit the game
                   2. Press TAB to see TOP 5 highscores
                   3. Press ENTER to start the game

Before pressing ENTER to start the game player has an option to enter any username he wishes, although username lenght is limited to 12 characters. If player does not enter anything, his username is by default set to "Unknown". 

# Commands

To move the snake player can only use arrow keys. Left arrow key(<-) to go left, right arrow key(->) to go right, exc. It is not possible for the snake to go downward if it is moving upward and vice versa, that also applies for left and right movement. Lastly, the snake can go through border and it will end up on the opposite side, so it is not game over if snake touches it.

# Files

For setting bigger text (SNAKE and GAME OVER in Main and End screen) on board program uses 2 files (menucoordinates.txt, endcoordinates.txt), they hold letter coordinates so make sure they are in your project directory. Every letter is sperated by the empty row, and every row is one line that makes a letter. For example, (1 1 2 2) represents x1, y1, x2, y2 and program draws a line from point 1 to point 2. Furthermore, highscores are saved in highscores.txt which means that file should also be in project directory.
