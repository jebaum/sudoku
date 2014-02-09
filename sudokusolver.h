#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

class SudokuBoard;
class SudokuBox;

class SudokuSolver
{
    public:
        SudokuSolver(SudokuBoard* gameboard);

        // core logic
        void solve(const float sleep_interval = 0);

    private:
        bool scanKnownValues(SudokuBox* box);
        bool isFilled() const;
        bool isValid() const;
        bool allDistinct(SudokuBox** box, const int size) const;

        SudokuBoard* board;
};

#endif  // SUDOKUSOLVER_H
