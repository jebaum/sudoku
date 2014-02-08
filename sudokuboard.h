#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

class SudokuBox;

class SudokuBoard
{
    public:
        SudokuBoard(int initial[][9]);
        bool isDone() const;
        bool isValid() const;
        void printBoard() const;
        SudokuBox getBox(const int r, const int c) const;
    private:
        SudokuBox** board;
};

#endif  // SUDOKUBOARD_H
