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
    return true;
}

bool SudokuSolver::eliminate(const int r, const int c, float sleep_interval)
{
    SudokuBox* box = board->getBox(r, c);
    bool made_progress = false;

    // if this box's final value is already set, no need to run function, and we've gained no new info
    if (box->getValue()) return made_progress;

    // scan row, column, and square and eliminate possible values
    if (eliminateRow(box))
        made_progress = true;
    if (eliminateColumn(box))
        made_progress = true;
    if (eliminateSquare(box))
        made_progress = true;

    /* TODO
    if one of the entries in a box's possible_value isn't in any of the other possible_value arrays for its row
        set that box's val to that entry
    same for column and square

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
    return made_progress;
}

bool SudokuSolver::eliminateRow(SudokuBox* box)
{
    bool made_progress = false;
    for (int i=0; i<9; ++i)
    {
        if (i == box->getColumn())
            continue; // don't compare against self

        int taken_value = board->getBox(box->getRow(), i)->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
            // cerr << "ROW ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
        }
    }
    return made_progress;
}

bool SudokuSolver::eliminateColumn(SudokuBox* box)
{
    bool made_progress = false;
    for (int i=0; i<9; ++i)
    {
        if (i == box->getRow())
            continue; // don't compare against self

        int taken_value = board->getBox(i, box->getColumn())->getValue();
        if (taken_value != 0 && box->isPossibleValue(taken_value))
        {
            box->setPossibleValue(taken_value, 0);
            made_progress = true;
            // cerr << "COL ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
        }
    }

    return made_progress;
}

bool SudokuSolver::eliminateSquare(SudokuBox* box)
{
    bool made_progress = false;
    int r = box->getRow();
    int c = box->getColumn();
    int r_upper_left = r - r % 3;
    int c_upper_left = c - c % 3;
    for (int i = r_upper_left; i < r_upper_left + 3; ++i)
    {
        for (int j = c_upper_left; j < c_upper_left + 3; ++j)
        {
            if (i == r && j == c) // don't compare against self
                continue;

            int taken_value = board->getBox(i, j)->getValue();
            if (taken_value != 0 && box->isPossibleValue(taken_value))
            {
                box->setPossibleValue(taken_value, 0);
                made_progress = true;
            // cerr << "SQU ELIMINATED " << taken_value << " FOR " << r << "," << c << endl;
            }
        }
    }
    return made_progress;
}

