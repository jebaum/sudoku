#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuBoard;
class SudokuBox;

class SudokuSolver
{
    public:
        SudokuSolver(SudokuBoard* gameboard);

        // core logic
        void solve(float sleep_interval = 0);
        bool isFilled() const;
        bool isValid() const; // TODO: implement this

    private:
        bool eliminate(const int r, const int c, const float sleep_interval = 0);
        bool eliminateRow(SudokuBox* box);
        bool eliminateColumn(SudokuBox* box);
        bool eliminateSquare(SudokuBox* box);

        SudokuBoard* board;
};

#endif  // SUDOKUSOLVER_H
