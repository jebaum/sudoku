#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "sudokusolver.h"
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuSolver::SudokuSolver(SudokuBoard* gameboard)
 : board(gameboard)
{ }

void SudokuSolver::solve(const float sleep_interval)
{
    bool made_progress = false;
    while (! isFilled())
    {
        made_progress = false;
        for (int r=0; r<9; ++r)
        {
            for (int c=0; c<9; ++c)
            {
                SudokuBox* box = board->getBox(r,c);
                if (box->getValue()) // if final value is already known, no need to work further on this box
                    continue;

                if (scanKnownValues(box))
                    made_progress = true;

                /* TODO more solving logic
                implement the techniques at this link:
                    http://www.sudokuoftheday.com/pages/techniques-overview.php
                */

                // see if we're down to one possible value
                int remaining_possible_values = 0;
                int maybe_value;
                for (int i=1; i < 10; ++i)
                {
                    if (box->isPossibleValue(i))
                    {
                        ++remaining_possible_values;
                        maybe_value = i;
                    }
                }
                if (remaining_possible_values == 1) // only one possible value left
                {
                    box->setValue(maybe_value);
                    made_progress = true;
                    #ifdef WINDOWS
                        system ("CLS");
                    #else
                        system ("clear");
                    #endif
                    board->printBoard(r, c);
                    usleep(1000 * 1000 * sleep_interval); // in microseconds, 1000 * 1000 = 1 second
                }
                else if (remaining_possible_values == 0)
                {
                    cerr << "no possible values, something's wrong\n";
                }
            }
        }

        if (! made_progress)
        {
            /* TODO guess and backtrack
                if we've gone through a full loop and haven't gained any new info, we're stuck
                    find the box with the least number of possible values and guess, then continue to iterate
                    if we end up with a valid solution, celebrate
                    if not, backtrack to the guess, make a different guess, and try again
            */
            cout << "I can't solve this! giving up...\n";
            break;
        }
    }
    return;
}

bool SudokuSolver::scanKnownValues(SudokuBox* box)
{
    bool made_progress = false;
    SudokuBox** same_row_boxes    = board->getRow(box, true);
    SudokuBox** same_column_boxes = board->getColumn(box, true);
    SudokuBox** same_square_boxes = board->getSquare(box, true);

    for (int i=0; i<8; ++i)
    {
        int taken_value = same_row_boxes[i]->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
        }

        taken_value = same_column_boxes[i]->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
        }

        taken_value = same_square_boxes[i]->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
        }
    }

    delete [] same_row_boxes;
    delete [] same_column_boxes;
    delete [] same_square_boxes;
    return made_progress;
}

bool SudokuSolver::isFilled() const
{
    for (int i=0; i<9; ++i)
        for (int j=0; j<9; ++j)
            if (! board->getBox(i,j)->getValue())
                return false;

    return true;
}

bool SudokuSolver::isValid() const
{
    bool valid_solution = true;
    // check no duplicate values in rows or columns
    for (int i=0; i<9; ++i)
    {
        SudokuBox** row    = board->getRow(board->getBox(i, 0));
        SudokuBox** column = board->getColumn(board->getBox(0, i));
        if (! allDistinct(row, 9) || ! allDistinct(column, 9))
            valid_solution = false;

        delete [] column;
        delete [] row;
    }

    for (int r=0; r<9; r+=3)
    {
        for (int c=0; c<9; c+=3)
        {
            SudokuBox** square = board->getSquare(board->getBox(r, c));
            if (! allDistinct(square, 9))
                valid_solution = false;

            delete [] square;
        }
    }

    return valid_solution;
}

bool SudokuSolver::allDistinct(SudokuBox** box, const int size) const
{
    bool taken[10] = {false};
    for (int i=0; i<size; ++i)
    {
        int current_value = box[i]->getValue();
        if (taken[current_value]) // we already found a box with this value
            return false;
        taken[current_value] = true;
    }
    return true;
}

