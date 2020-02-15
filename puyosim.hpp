#ifndef PUYOSIM_HPP_2020_02
#define PUYOSIM_HPP_2020_02

#include <vector>
#include <map>
#include <string>

namespace PuyoSim {

inline std::map<std::string, char> COLOR = {
    {"NONE", '0'},
    {"RED", 'R'},
    {"GREEN", 'G'},
    {"BLUE", 'B'},
    {"YELLOW", 'Y'},
    {"PURPLE", 'P'},
    {"GARBAGE", 'J'},
    {"HARD", 'H'},
    {"BLOCK", 'B'}
};

class Puyo {
public:
    char p;
    int x;
    int y;

    bool isEqual(Puyo& puyo);
    bool isGarbage();
};

using PuyoGroup = std::vector<Puyo>;
using PuyoGroups = std::vector<std::vector<Puyo>>;

inline constexpr int DEFAULT_COLS { 6 };
inline constexpr int DEFAULT_ROWS { 13 };
inline constexpr int DEFAULT_HROWS { 1 }; // Hidden rows

class Matrix {
public:
    std::vector<Puyo> m_data;
    int m_rows;
    int m_cols;
    int m_hrows;

    Matrix(
        int rows = DEFAULT_ROWS,
        int cols = DEFAULT_COLS,
        int hrows = DEFAULT_HROWS
    );

    Puyo* puyoAt(int x, int y);
    void setPuyo(char color, int x, int y);
    void setTestChain();

    PuyoGroups nextColorPops();
    // PuyoGroup nextGarbagePops(PuyoGroups& coloredPuyo);

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