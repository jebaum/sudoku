# Sudoku Solver in C++

tested on linux, no idea if clearing the screen will work properly in windows

`sudoku` can take up to two arguments:\
	* number of seconds to initially sleep after displaying the game board
		+ default is 1
	* number of seconds to sleep after finding a value (can be a decimal)
		+ default is 0

if nothing (or the value 0) is passed, the puzzle will probably solve instantly and you won't get to watch it fill in values slowly which can be fun
