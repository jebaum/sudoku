#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuBoard;
class SudokuBox;

class SudokuSolver
{
    public:
        SudokuSolver(SudokuBoard* gameboard);

        // core logic
        void solve(const float sleep_interval = 0); // TODO take over eliminate functionality? no double wrapping

    private:
        bool eliminate(const int r, const int c, const float sleep_interval = 0); // TODO better name for this
        bool scanKnownValues(SudokuBox* box);
        bool checkLastPossibleRow(SudokuBox* box);
        bool checkLastPossibleColumn(SudokuBox* box);
        bool checkLastPossibleSquare(SudokuBox* box);
        bool isFilled() const;
        bool isValid() const;

        SudokuBoard* board;
};

#endif  // SUDOKUSOLVER_H
