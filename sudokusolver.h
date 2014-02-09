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

    private:
        bool eliminate(const int r, const int c, const float sleep_interval = 0);
        bool eliminateRow(SudokuBox* box);
        bool eliminateColumn(SudokuBox* box);
        bool eliminateSquare(SudokuBox* box);
        bool checkLastPossibleRow(SudokuBox* box);
        bool checkLastPossibleColumn(SudokuBox* box);
        bool checkLastPossibleSquare(SudokuBox* box);
        bool isFilled() const;
        bool isValid() const; // TODO: implement this

        SudokuBoard* board;
};

#endif  // SUDOKUSOLVER_H
