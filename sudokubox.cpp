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

bool SudokuBox::eliminate()
{
    // if this box's final value is already set, no need to run function, and we've gained no new info
    bool didsomething = false;
    if (val) return didsomething;

    // TODO: make sure I don't overwrite a 'didsomething' that's already true
    didsomething = eliminateRow();
    didsomething = eliminateColumn();
    didsomething = eliminateSquare();

    // see if we're down to one possible value
    int count = 0;
    int maybeval;
    for (int i=1; i < 10; ++i)
    {
        if (possible_value[i])
        {
            ++count;
            maybeval = i;
        }
    }

    if (count == 1) // only one possible value left
    {
        val = maybeval;
        didsomething = true;
        #ifdef WINDOWS
            system ( "CLS" );
        #else
            system ("clear");
        #endif
        board->printBoard(r, c);
        usleep(1000 * 1000 * .5); // in microseconds, 1000 * 1000 = 1 second
    }
    else if (count == 0)
    {
        cerr << "no possible values, something's wrong\n";
        return false;
    }
    return didsomething;
}

bool SudokuBox::eliminateRow()
{
    bool didsomething = false;
    for (int i=0; i<9; ++i)
    {
        if (i == c)
            continue; // don't compare against self

        int temp = board->getBox(r, i)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            didsomething = true;
            // cerr << "ROW ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }
    return didsomething;
}

bool SudokuBox::eliminateColumn()
{
    bool didsomething = false;
    for (int i=0; i<9; ++i)
    {
        if (i == r)
            continue; // don't compare against self

        int temp = board->getBox(i, c)->getValue();
        if (temp != 0 && possible_value[temp])
        {
            possible_value[temp] = 0;
            didsomething = true;
            // cerr << "COL ELIMINATED " << temp << " FOR " << r << "," << c << endl;
        }
    }

    return didsomething;
}

bool SudokuBox::eliminateSquare()
{
    bool didsomething = false;
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
                didsomething = true;
            // cerr << "SQU ELIMINATED " << temp << " FOR " << r << "," << c << endl;
            }
        }
    }
    return didsomething;
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

/*
    for eliminate: eliminate things from possible_value if that box's square,row,or column already has a box with that val
                   if one of the entries in a box's possible_value isn't in any of the other possible_value arrays for its row, set that val to that entry
                       same for column and square
*/
