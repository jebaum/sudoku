#include <iostream>
#include "sudokuboard.h"
#include "sudokubox.h"

using namespace std;

SudokuBoard::SudokuBoard()
{
    board = new SudokuBox*[9];
    for (int i=0; i<9; ++i)
        board[i] = new SudokuBox[9];

}

void SudokuBoard::printBoard() const
{
    cout << endl;
    cout << "    ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓" << endl;

    for (int i=0; i<9; ++i)
    {
        for (int j=0; j<9; ++j)
        {
            if (j==0)
                cout << "    ┃ ";

            cout << board[i][j].getValue();
            cout <<  ((j+1)%3 ? " │ " : " ┃ ");
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

SudokuBox SudokuBoard::getBox(const int r, const int c) const
{
    return board[r][c];
}
