#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

class SudokuBoard;

class SudokuBox
{
    public:
        SudokuBox();

        // accessors
        int  getRow() const;
        int  getColumn() const;
        int  getValue() const;
        bool getPossibleValue(const int value) const;

        // mutators
        void setValue(const int value);
        void setPossibleValue(const int value, const bool possible);
        void setupBox(SudokuBoard* gameboard, const int r, const int c);

        // helpers
        void printPossibleValues() const;

    private:
        SudokuBoard* board;
        int r;
        int c;
        int val;
        bool possible_value[10];
};

#endif  // SUDOKUBOX_H
