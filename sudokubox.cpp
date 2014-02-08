#include <iostream>
#include "sudokubox.h"


SudokuBox::SudokuBox()
 : val(0)
{
    for (int i=0; i<10; ++i)
        possible_values[i] = 1;
}

unsigned char SudokuBox::getValue() const
{
    return (val ? val + '0' : ' ');
}

void SudokuBox::setValue(const unsigned char value)
{
    if (value < 1 || value > 9)
        std::cerr << "invalid value\n";
    val = value;
}
