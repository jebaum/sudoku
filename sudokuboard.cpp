#include <iostream>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuBoard::SudokuBoard(int initial[][9])
{
    board = new SudokuBox*[9];
    for (int i=0; i<9; ++i)
        board[i] = new SudokuBox[9];

    for (int i=0; i<9; ++i)
    {
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

bool SudokuBoard::isDone() const
{
    for (int i=0; i<9; ++i)
        for (int j=0; j<9; ++j)
            if (!board[i][j].getValue())
                return false;

    return true;
}

void SudokuBoard::printBoard() const
{
    cout << endl;
    cout << "    ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓" << endl;

    for (int i=0; i<9; ++i)
    {
        cout << "    ┃ ";
        for (int j=0; j<9; ++j)
            cout << board[i][j].getPrintableValue() << ((j+1)%3 ? " │ " : " ┃ ");

        cout << endl;
        if ((i+1)%3)
            cout << "    ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨" << endl;
        else if (i != 8)
        cout << "    ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫" << endl;
    }

    cout << "    ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛" << endl;
    cout << endl;

}

SudokuBox* SudokuBoard::getBox(const int r, const int c) const
{
    return &board[r][c];
}

