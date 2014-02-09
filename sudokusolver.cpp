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
    // check no duplicate values in row
    for (int r=0; r<9; ++r)
    {
        bool taken[10] = {false};
        for (int c=0; c<9; ++c)
        {
            int box_value = board->getBox(r,c)->getValue();
            if (taken[box_value])
            {
                return false;
            }
            taken[box_value] = true;
        }
    }

    // check no duplicate values in column
    for (int c=0; c<9; ++c)
    {
        bool taken[10] = {false};
        for (int r=0; r<9; ++r)
        {
            int box_value = board->getBox(r,c)->getValue();
            if (taken[box_value])
            {
                return false;
            }
            taken[box_value] = true;
        }
    }

    // TODO check no duplicate values in square

    return true;
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

