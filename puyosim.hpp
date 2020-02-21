#ifndef PUYOSIM_HPP_2020_02
#define PUYOSIM_HPP_2020_02

#include <vector>
#include <map>
#include <string>
#include <tuple>
#include "puyo.hpp"

namespace PuyoSim {

constexpr int DEFAULT_COLS{ 6 };
constexpr int DEFAULT_ROWS{ 13 };
constexpr int DEFAULT_HROWS{ 1 }; // Hidden rows
constexpr int DEFAULT_PUYOTOCLEAR{ 4 };
constexpr int DEFAULT_TARGETPOINT{ 70 };

const std::vector<int> CHAIN_POWERS {
    0, 8, 16, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, 544, 576, 608, 640, 672
};

const std::vector<int> COLOR_BONUS {
    0, 3, 6, 12, 24
};

const std::vector<int> GROUP_BONUS {
    0, 2, 3, 4, 5, 6, 7, 10
};


class Matrix {
public:
    std::vector<Puyo> m_data;
    int m_rows;
    int m_cols;
    int m_hrows;
    int m_puyoToClear;
    int m_targetPoint;

    Matrix(
        int rows = DEFAULT_ROWS,
        int cols = DEFAULT_COLS,
        int hrows = DEFAULT_HROWS,
        int puyoToClear = DEFAULT_PUYOTOCLEAR,
        int targetPoint = DEFAULT_TARGETPOINT
    );

    Puyo* puyoAt(int i);
    Puyo* puyoAt(int x, int y);
    void setPuyo(char color, int x, int y);
    void setTestChain(int i);
    size_t size();
    std::tuple<int, std::vector<char>> usedColors();

    void print();
};

/**
 * Finds the groups of Puyo that reach the Puyo to Clear requirement
 * @param mat Puyo Matrix
 * @returns Vector of groups (itself a vector) of pointers to Puyos.
 */
PuyoPtrGroups nextColorPops(Matrix& mat);

/**
 * Finds the Garbage Puyos adjacent to popping groups.
 * Some Garbage Puyos are added in duplicate if the same one is adjacent
 * to multiple Puyos. This is to help with popping Hard Puyos later on.
 * @param mat Puyo Matrix
 * @param nextColors Vector of groups (itself a vector) of pointers to Puyos that will pop.
 * @returns Vector of pointers to Garbage Puyos that need to clear. Not necessarily a unique set.
 */
PuyoPtrGroup nextGarbagePops(Matrix& mat, PuyoPtrGroups& nextColors);

/**
 * Pop the colored Puyos, with the side effect of mutating the matrix the Puyos came from.
 * @param nextColors Vector of groups (itself a vector) of pointers to Puyos that will pop.
 */
void popColoredPuyos(PuyoPtrGroups& nextColors);

/**
 * Pop the Garbage Puyos, with the side effect of mutating the matrix the Garbage came from.
 * @param nextGarbage Vector of pointers to Garbage Puyos that need to clear.
 */
void popGarbagePuyos(PuyoPtrGroup& nextGarbage);

/**
 * Apply gravity to a Puyo Matrix
 * @param mat Puyo Matrix
 */
void dropPuyos(Matrix& mat);

/**
 * Calculate the score generated from a step's pop.
 * Doesn't factor in leftover nuisance points from previous chains/steps.
 * @param mat Puyo Matrix
 * @param nextColors Vector of groups (itself a vector) of pointers to Puyos that will pop.
 * @param step The current chain length
 */
int calcStepScore(Matrix& mat, PuyoPtrGroups& nextColors, int step);

/**
 * Calculate the amount of garbage generated from the provided score, using the
 * matrix's target point setting.
 * @param mat Puyo Matrix
 * @param score Total score of the chain
 */
int calcChainGarbage(Matrix& mat, int score);

/**
 * Fully simulate the chain, mutating the original matrix.
 * @param mat Puyo Matrix
 * @returns Chain Length, Score, Garbage Total
 */
std::tuple<int, int, int> simulateChain(Matrix& mat);

class BoolMatrix {
public:
    std::vector<bool> m_data;
    int m_rows;
    int m_cols;

    BoolMatrix(int rows = DEFAULT_ROWS, int cols = DEFAULT_COLS);

    bool get(int x, int y);
    void set(bool b, int x, int y);
};

}

#endif /* PUYOSIM_HPP */