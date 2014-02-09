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
        // TODO helper function to return array of SudokuBox pointers
        // array would contain pointers to the other boxes in the same square as the passed box
        // Sudokubox* getSquaresOtherBoxes(SudokuBox* box) const;

        // helpers
        void printBoard(int r, int c) const;
        void printBoard() const;

    private:
        SudokuBox** board;
};

#endif  // SUDOKUBOARD_H
