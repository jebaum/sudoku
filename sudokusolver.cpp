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

void SudokuSolver::solve(float sleep_interval)
{
    bool made_progress = false;
    while (! isFilled())
    {
        made_progress = false;
        for (int r=0; r<9; ++r)
        {
            for (int c=0; c<9; ++c)
            {
                if (eliminate(r, c, sleep_interval))
                    made_progress = true;
            }
        }
        if (! made_progress)
        {
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

bool SudokuSolver::eliminate(const int r, const int c, float sleep_interval)
{
    SudokuBox* box = board->getBox(r, c);
    bool made_progress = false;

    // if this box's final value is already set, no need to run function, and we've gained no new info
    if (box->getValue()) return made_progress;

    // scan row, column, and square and eliminate possible values
    if (scanKnownValues(box))
        made_progress = true;
    if (checkLastPossibleRow(box))
        made_progress = true;
    if (checkLastPossibleColumn(box))
        made_progress = true;

    /* TODO more solving logic
    implement the techniques at this link:
        http://www.sudokuoftheday.com/pages/techniques-overview.php

    guess and backtrack
        if we've called eliminate() on every box and haven't gained any new info, we're stuck
            find the box with the least number of possible values and guess, then continue to iterate
            if we end up with a valid solution, celebrate
            if not, backtrack to the guess, make a different guess, and try again
    */

    // see if we're down to one possible value
    int remaining_possible_values = 0;
    int maybeval;
    for (int i=1; i < 10; ++i)
    {
        if (box->isPossibleValue(i))
        {
            ++remaining_possible_values;
            maybeval = i;
        }
    }
    if (remaining_possible_values == 1) // only one possible value left
    {
        box->setValue(maybeval);
        made_progress = true;
        #ifdef WINDOWS
            system ( "CLS" );
        #else
            system ("clear");
        #endif
        board->printBoard(r, c);
        usleep(1000 * 1000 * sleep_interval); // in microseconds, 1000 * 1000 = 1 second
    }
    else if (remaining_possible_values == 0)
    {
        cerr << "no possible values, something's wrong\n";
        return false;
    }
    else
    {
        box->printPossibleValues();
    }
    return made_progress;
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
            // cerr << "ROW ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
        }
        taken_value = same_column_boxes[i]->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
            // cerr << "ROW ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
        }
        taken_value = same_square_boxes[i]->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
            // cerr << "ROW ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
        }
    }

    delete [] same_row_boxes;
    delete [] same_column_boxes;
    delete [] same_square_boxes;
    return made_progress;
}

bool SudokuSolver::checkLastPossibleRow(SudokuBox* box)
{
    bool made_progress = false;
    bool only_in_current[10];
    for (int i=0; i<10; ++i)
        only_in_current[i] = box->isPossibleValue(i);

    for (int c=0; c<9; ++c)
    {
        if (c == box->getColumn())
            continue; // don't compare against self

        for (int i=1; i<10; ++i)
        {
            if (board->getBox(box->getRow(), c)->isPossibleValue(i))
            {
                only_in_current[i] = false;
            }
        }
    }

    int unique_possible_values = 0;
    int maybeval;
    for (int i=1; i<10; ++i)
    {
        if (only_in_current[i])
        {
            ++unique_possible_values;
            maybeval = i;
        }
    }
    if (unique_possible_values == 1)
    {
        box->setValue(maybeval);
        made_progress = true;
    }

    return made_progress;
}

bool SudokuSolver::checkLastPossibleColumn(SudokuBox* box)
{
    bool made_progress = false;
    bool only_in_current[10];
    for (int i=0; i<10; ++i)
        only_in_current[i] = box->isPossibleValue(i);

    for (int r=0; r<9; ++r)
    {
        if (r == box->getRow())
            continue; // don't compare against self

        for (int i=1; i<10; ++i)
        {
            if (board->getBox(r, box->getColumn())->isPossibleValue(i))
            {
                only_in_current[i] = false;
            }
        }
    }

    int unique_possible_values = 0;
    int maybeval;
    for (int i=1; i<10; ++i)
    {
        if (only_in_current[i])
        {
            ++unique_possible_values;
            maybeval = i;
        }
    }
    if (unique_possible_values == 1)
    {
        box->setValue(maybeval);
        made_progress = true;
    }

    return made_progress;
}

bool SudokuSolver::checkLastPossibleSquare(SudokuBox* box)
{
    // TODO implement checkLastPossibleSquare
    bool made_progress = false;

    return made_progress;
}
