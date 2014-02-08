#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuBox::SudokuBox()
 : val(0)
{
    for (int i=0; i<10; ++i)
        possible_value[i] = 1;
}

bool SudokuBox::eliminate(float sleep_interval)
{
    bool did_something = false;

    // if this box's final value is already set, no need to run function, and we've gained no new info
    if (val) return did_something;

    // scan row, column, and square and eliminate possible values
    if (eliminateRow())
        did_something = true;
    if (eliminateColumn())
        did_something = true;
    if (eliminateSquare())
        did_something = true;

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
        did_something = true;
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
    return did_something;
}

bool SudokuBox::eliminateRow()
{
    bool did_something = false;
    for (int i=0; i<9; ++i)
    {
        if (i == c)
            continue; // don't compare against self

        int temp = board->getBox(r, i)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            did_something = true;
            // cerr << "ROW ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }
    return did_something;
}

bool SudokuBox::eliminateColumn()
{
    bool did_something = false;
    for (int i=0; i<9; ++i)
    {
        if (i == r)
            continue; // don't compare against self

        int temp = board->getBox(i, c)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            did_something = true;
            // cerr << "COL ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }

    return did_something;
}

bool SudokuBox::eliminateSquare()
{
    bool did_something = false;
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
                did_something = true;
            // cerr << "SQU ELIMINATED " << temp << " FOR " << r << "," << c << endl;
            }
        }
    }
    return did_something;
}

int SudokuBox::getValue() const
{
    return val;
}

char SudokuBox::getPrintableValue() const
{
    return (val ? val + '0' : ' ');
}

void SudokuBox::setValue(const int value)
{
    if (value < 1 || value > 9)
        cerr << "invalid value\n";
    val = value;
}

void SudokuBox::setupBox(SudokuBoard* gameboard, int row, int col)
{
    board = gameboard;
    r = row;
    c = col;
}

void SudokuBox::printPossibleValues()
{
    cerr << "(" << r << "," << c << "): ";
    for (int i=1; i<10; ++i)
    {
        if (possible_value[i] != 0)
            cerr << i << " ";
    }
    cerr << endl;
}
