#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

class SudokuBox;

class SudokuBoard
{
    public:
        SudokuBoard(int initial[][9]);
        ~SudokuBoard();

        // accessors
        SudokuBox* getBox(const int r, const int c) const;

        // helpers
        void printBoard(int r, int c) const;
        void printBoard() const;
    private:
        SudokuBox** board;
};

#endif  // SUDOKUBOARD_H
