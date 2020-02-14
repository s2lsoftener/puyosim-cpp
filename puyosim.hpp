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
    {"GARBAGE", 'J'}
};

inline constexpr int DEFAULT_COLS { 6 };
inline constexpr int DEFAULT_ROWS { 13 };
inline constexpr int DEFAULT_HROWS { 1 }; // Hidden rows
class Matrix {
public:
    std::vector<char> m_data;
    int m_rows;
    int m_cols;
    int m_hrows;

    Matrix(
        int rows = DEFAULT_ROWS,
        int cols = DEFAULT_COLS,
        int hrows = DEFAULT_HROWS
    );

    char colorAt(int x, int y);
    void setColor(char p, int x, int y);
    void setTestChain();

    void print();
};

}

#endif /* PUYOSIM_HPP */