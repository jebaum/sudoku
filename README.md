# Sudoku Solver in C++

tested on linux, no idea if clearing the screen will work properly in windows

`sudoku` can take up to two arguments:

1. number of seconds to initially sleep after displaying the game board (default is`1`)

2. number of seconds to sleep after finding a value (can be a decimal) (default is`0`)

Example: `./sudoku 2 .5`

if nothing (or the value 0) is passed as the second parameter, the puzzle will probably solve instantly and you won't get to watch it fill in values slowly. this is good for if you hate fun or cool things.


## TODO
 * have solver work on a copy of the gameboard instead of modifying the original

 * all the todo markers in the files

