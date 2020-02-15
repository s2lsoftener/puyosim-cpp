#ifndef PUYOSIM_HPP_2020_02
#define PUYOSIM_HPP_2020_02

#include <vector>
#include <map>
#include <string>
#include "puyo.hpp"

namespace PuyoSim {

constexpr int DEFAULT_COLS{ 6 };
constexpr int DEFAULT_ROWS{ 13 };
constexpr int DEFAULT_HROWS{ 1 }; // Hidden rows

class Matrix {
public:
    std::vector<Puyo> m_data;
    int m_rows;
    int m_cols;
    int m_hrows;
    PuyoPtrGroups m_nextColorPops;
    PuyoPtrGroup m_nextGarbagePops;

    Matrix(
        int rows = DEFAULT_ROWS,
        int cols = DEFAULT_COLS,
        int hrows = DEFAULT_HROWS
    );

    Puyo* puyoAt(int x, int y);
    void setPuyo(char color, int x, int y);
    void setTestChain(int i);

    PuyoPtrGroups nextColorPops();
    PuyoPtrGroup nextGarbagePops(PuyoPtrGroups nextColors);

    void print();
};


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