#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuBox::SudokuBox()
 : val(0)
{
    memset(possible_value, 1, sizeof(possible_value));
}

bool SudokuBox::eliminate(float sleep_interval)
{
    bool made_progress = false;

    // if this box's final value is already set, no need to run function, and we've gained no new info
    if (val) return made_progress;

    // scan row, column, and square and eliminate possible values
    if (eliminateRow())
        made_progress = true;
    if (eliminateColumn())
        made_progress = true;
    if (eliminateSquare())
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
        if (possible_value[i])
        {
            ++remaining_possible_values;
            maybeval = i;
        }
    }
    if (remaining_possible_values == 1) // only one possible value left
    {
        val = maybeval;
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

bool SudokuBox::eliminateRow()
{
    bool made_progress = false;
    for (int i=0; i<9; ++i)
    {
        if (i == c)
            continue; // don't compare against self

        int temp = board->getBox(r, i)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            made_progress = true;
            // cerr << "ROW ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }
    return made_progress;
}

bool SudokuBox::eliminateColumn()
{
    bool made_progress = false;
    for (int i=0; i<9; ++i)
    {
        if (i == r)
            continue; // don't compare against self

        int temp = board->getBox(i, c)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            made_progress = true;
            // cerr << "COL ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }

    return made_progress;
}

bool SudokuBox::eliminateSquare()
{
    bool made_progress = false;
    int r_upper_left = r - r % 3;
    int c_upper_left = c - c % 3;
    for (int i = r_upper_left; i < r_upper_left + 3; ++i)
    {
        for (int j = c_upper_left; j < c_upper_left + 3; ++j)
        {
            if (i == r && j == c) // don't compare against self
                continue;

            int temp = board->getBox(i, j)->getValue();
            if (temp != 0 && possible_value[temp])
            {
                possible_value[temp] = 0;
                made_progress = true;
            // cerr << "SQU ELIMINATED " << temp << " FOR " << r << "," << c << endl;
            }
        }
    }
    return made_progress;
}

int SudokuBox::getValue() const
{
    return val;
}

void SudokuBox::setValue(const int value)
{
    if (value < 1 || value > 9)
        cerr << "invalid value\n";
    val = value;
}

void SudokuBox::setupBox(SudokuBoard* gameboard, const int row, const int col)
{
    board = gameboard;
    r = row;
    c = col;
}

void SudokuBox::printPossibleValues() const
{
    cerr << "(" << r << "," << c << "): ";
    for (int i=1; i<10; ++i)
    {
        if (possible_value[i] != 0)
            cerr << i << " ";
    }
    cerr << endl;
}
