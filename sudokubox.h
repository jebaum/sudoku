#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

class SudokuBoard;

class SudokuBox
{
    public:
        SudokuBox();
        bool eliminate();
        bool eliminateRow();
        bool eliminateColumn();
        bool eliminateSquare();
        int getValue() const;
        char getPrintableValue() const;
        void setValue(const int val);
        void setupBox(SudokuBoard* gameboard, int r, int c);
        void printPossibleValues();

    private:
        SudokuBoard* board;
        int possible_value[10];
        int r;
        int c;
        int val;
};

#endif  // SUDOKUBOX_H
