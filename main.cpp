#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "sudokusolver.h"
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;


int main(int argc, char** argv)
{
    float sleep_interval = 0;
    int initial_delay = 1;
    if (argc > 1)
        initial_delay = atoi(argv[1]);
    if (argc > 2)
        sleep_interval = atof(argv[2]);

    int game1_easy[9][9] =  {
        {6, 0, 0,  1, 0, 8,  2, 0, 3},
        {0, 2, 0,  0, 4, 0,  0, 9, 0},
        {8, 0, 3,  0, 0, 5,  4, 0, 0},

        {5, 0, 4,  6, 0, 7,  0, 0, 9},
        {0, 3, 0,  0, 0, 0,  0, 5, 0},
        {7, 0, 0,  8, 0, 3,  1, 0, 2},

        {0, 0, 1,  7, 0, 0,  9, 0, 6},
        {0, 8, 0,  0, 3, 0,  0, 2, 0},
        {3, 0, 2,  9, 0, 4,  0, 0, 5},
    };

    SudokuBoard* myboard = new SudokuBoard(game1_easy);
    SudokuSolver* solver = new SudokuSolver(myboard);
    myboard->printBoard();
    sleep(initial_delay);
    solver->solve(sleep_interval);
    delete myboard;
    delete solver;

    // can't yet actually solve this
    int game2_hard[9][9] =  {
        {0, 0, 0,  0, 0, 0,  0, 0, 0},
        {0, 0, 0,  0, 0, 3,  0, 7, 5},
        {0, 0, 1,  0, 2, 0,  0, 0, 0},

        {0, 0, 0,  5, 0, 7,  0, 0, 0},
        {0, 0, 4,  0, 0, 0,  1, 0, 0},
        {0, 9, 0,  0, 0, 0,  0, 0, 0},

        {5, 0, 0,  0, 0, 0,  0, 7, 3},
        {0, 0, 2,  0, 1, 0,  0, 0, 0},
        {0, 0, 0,  0, 4, 0,  0, 0, 9},
    };


    myboard = new SudokuBoard(game2_hard);
    solver  = new SudokuSolver(myboard);
    myboard->printBoard();
    sleep(initial_delay);
    solver->solve(sleep_interval);
    delete myboard;
    delete solver;

    cout << "Finished running\n";
    return 0;
}
