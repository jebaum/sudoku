#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

class SudokuBoard;

class SudokuBox
{
    public:
        SudokuBox();
        bool eliminate();
        unsigned char getValue() const;
        void setValue(const unsigned char val);

    private:
        SudokuBoard*  board;
        unsigned char possible_values[10];
        unsigned char val;
};

#endif  // SUDOKUBOX_H
