#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#define UNASSIGNED 0
#define N 9

class Sudoku {
public:
    Sudoku();
    void printGrid();
    bool solveSudoku();
    bool generateSudoku(int emptySpaces);

private:
    int grid[N][N];
    bool isSafe(int row, int col, int num);
    bool findUnassignedLocation(int &row, int &col);
    void fillDiagonal();
    void fillBox(int row, int col);
    void removeKDigits(int K);
    int randomGenerator(int num);
    bool usedInRow(int row, int num);
    bool usedInCol(int col, int num);
    bool usedInBox(int boxStartRow, int boxStartCol, int num);
};

Sudoku::Sudoku() {
    srand(time(0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = UNASSIGNED;
    fillDiagonal();
}

void Sudoku::printGrid() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

bool Sudoku::solveSudoku() {
    int row, col;
    if (!findUnassignedLocation(row, col))
        return true; // success!
    for (int num = 1; num <= N; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku())
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}

bool Sudoku::generateSudoku(int emptySpaces) {
    solveSudoku();
    removeKDigits(emptySpaces);
    return true;
}

bool Sudoku::isSafe(int row, int col, int num) {
    return !usedInRow(row, num) &&
           !usedInCol(col, num) &&
           !usedInBox(row - row % 3, col - col % 3, num);
}

bool Sudoku::findUnassignedLocation(int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

void Sudoku::fillDiagonal() {
    for (int i = 0; i < N; i += 3)
        fillBox(i, i);
}

void Sudoku::fillBox(int row, int col) {
    int num;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            do {
                num = randomGenerator(N);
            } while (!isSafe(row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}

void Sudoku::removeKDigits(int K) {
    int count = K;
    while (count != 0) {
        int cellId = randomGenerator(N * N);
        int i = (cellId / N);
        int j = cellId % 9;
        if (j != 0)
            j = j - 1;
        if (grid[i][j] != UNASSIGNED) {
            count--;
            grid[i][j] = UNASSIGNED;
        }
    }
}

int Sudoku::randomGenerator(int num) {
    return rand() % num + 1;
}

bool Sudoku::usedInRow(int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::usedInCol(int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::usedInBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

int main() {
    Sudoku sudoku;
    int emptySpaces = 40; // Number of empty spaces in the generated Sudoku
    sudoku.generateSudoku(emptySpaces);
    cout << "Generated Sudoku Puzzle:" << endl;
    sudoku.printGrid();
    cout << endl;

    if (sudoku.solveSudoku()) {
        cout << "Solved Sudoku Puzzle:" << endl;
        sudoku.printGrid();
    } else {
        cout << "No solution exists";
    }

    return 0;
}
