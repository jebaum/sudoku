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

void SudokuBoard::printBoard(int r, int c) const
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

            // TODO clean up this logic
            char val_to_print = '0' + board[i][j].getValue();
            if (val_to_print == '0') val_to_print = ' ';

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

