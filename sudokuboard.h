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
        // these three functions return a pointer that the caller must delete []
        // if exclude is true, the box pointer passed as the first parameter isn't included in the array
        SudokuBox** getRow(const SudokuBox* box, const bool exclude = false) const;
        SudokuBox** getColumn(const SudokuBox* box, const bool exclude = false) const;
        SudokuBox** getSquare(const SudokuBox* box, const bool exclude = false) const;

        // helpers
        void printBoard(const int r, const int c) const;
        void printBoard() const;

    private:
        SudokuBox** board;
};

#endif  // SUDOKUBOARD_H
