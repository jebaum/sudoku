#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

class SudokuBoard;

class SudokuBox
{
    public:
        SudokuBox();

        // core logic
        bool eliminate(float sleep_interval = 0);
        bool eliminateRow();
        bool eliminateColumn();
        bool eliminateSquare();

        // accessors
        int  getValue() const;

        // mutators
        void setValue(const int val);
        void setupBox(SudokuBoard* gameboard, const int r, const int c);

        // helpers
        void printPossibleValues() const;

    private:
        SudokuBoard* board;
        int possible_value[10];
        int r;
        int c;
        int val;
};

#endif  // SUDOKUBOX_H
