#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

class SudokuBox;

class SudokuBoard
{
    public:
        SudokuBoard(int initial[][9]);
        ~SudokuBoard();
        bool isDone() const;
        bool isValid() const; // TODO: implement this
        void printBoard(int r, int c) const;
        void printBoard() const;
        SudokuBox* getBox(const int r, const int c) const;
    private:
        SudokuBox** board;
};

#endif  // SUDOKUBOARD_H
