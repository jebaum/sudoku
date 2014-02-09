#include <iostream>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuBoard::SudokuBoard(int initial[][9])
{
    board = new SudokuBox*[9];

    for (int i=0; i<9; ++i)
    {
        board[i] = new SudokuBox[9];
        for (int j=0; j<9; ++j)
        {
            board[i][j].setupBox(this,i,j);
            if (initial[i][j] != 0)
            {
                board[i][j].setValue(initial[i][j]);
            }
        }
    }
}

SudokuBoard::~SudokuBoard()
{
    for (int i=0; i<9; ++i)
        delete [] board[i];

    delete [] board;
}

SudokuBox* SudokuBoard::getBox(const int r, const int c) const
{
    return &board[r][c];
}

SudokuBox** SudokuBoard::getRow(const SudokuBox* box, const bool exclude) const
{
    int size = 8 + (exclude ? 0 : 1);
    SudokuBox** boxes = new SudokuBox*[size];
    int index = 0;
    int r = box->getRow();
    int c = box->getColumn();

    for (int i=0; i<9; ++i)
    {
        if (i == c && exclude)
            continue;
        boxes[index++] = getBox(r, i);
    }
    return boxes;
}

SudokuBox** SudokuBoard::getColumn(const SudokuBox* box, const bool exclude) const
{
    int size = 8 + (exclude ? 0 : 1);
    SudokuBox** boxes = new SudokuBox*[size];
    int index = 0;
    int r = box->getRow();
    int c = box->getColumn();

    for (int i=0; i<9; ++i)
    {
        if (i == r && exclude)
            continue;
        boxes[index++] = getBox(i, c);
    }
    return boxes;
}

SudokuBox** SudokuBoard::getSquare(const SudokuBox* box, const bool exclude) const
{
    int size = 8 + (exclude ? 0 : 1);
    SudokuBox** boxes = new SudokuBox*[size];
    int index = 0;
    int r = box->getRow();
    int c = box->getColumn();
    int r_upper_left = r - r % 3;
    int c_upper_left = c - c % 3;
    for (int i = r_upper_left; i < r_upper_left + 3; ++i)
    {
        for (int j = c_upper_left; j < c_upper_left + 3; ++j)
        {
            if (i == r && j == c && exclude)
                continue;
            boxes[index++] = getBox(i, j);
        }
    }

    return boxes;
}

void SudokuBoard::printBoard(const int r, const int c) const
{

    cout << endl;
    cout << "    ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓" << endl;

    for (int i=0; i<9; ++i)
    {
        cout << "    ┃ ";
        for (int j=0; j<9; ++j)
        {
            if (i == r && j == c)
                cout << "\033[1;31m";

            char val_to_print = '0' + board[i][j].getValue();
            if (val_to_print == '0')
                val_to_print = ' ';

            cout << val_to_print << "\033[0m" << ((j+1)%3 ? " │ " : " ┃ ");
        }

        cout << endl;
        if ((i+1)%3)
            cout << "    ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨" << endl;
        else if (i != 8)
        cout << "    ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫" << endl;
    }

    cout << "    ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛" << endl;
    cout << endl;

}

void SudokuBoard::printBoard() const
{
    printBoard(-1, -1);
}

