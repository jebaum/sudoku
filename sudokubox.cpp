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

int SudokuBox::getRow() const
{
    return r;
}

int SudokuBox::getColumn() const
{
    return c;
}

int SudokuBox::getValue() const
{
    return val;
}

bool SudokuBox::isPossibleValue(const int value) const
{
    return possible_value[value];
}

void SudokuBox::setValue(const int value)
{
    if (value < 1 || value > 9)
        cerr << "invalid value\n";
    val = value;
}

void SudokuBox::setPossibleValue(const int value, const bool possible)
{
    possible_value[value] = possible;
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

