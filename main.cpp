#include <iostream>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;


int main()
{
    int game1[9][9] =  {
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

    SudokuBoard* myboard = new SudokuBoard(game1);
    myboard->printBoard();

    if (myboard->isDone())
        cout << "board is filled in\n";
    else
        cout << "board is not filled in\n";

    int x=0;
    while (x < 3)
    {
        cout << endl << endl << "BEGINNING ITERATION " << x+1 << endl << endl;
        for (int r=0; r<9; ++r)
        {
            for (int c=0; c<9; ++c)
            {
                myboard->getBox(r, c)->eliminate();
            }
        }
        ++x;
    }

    myboard->printBoard();
    delete myboard;
    return 0;

}
