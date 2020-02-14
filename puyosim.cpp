#include <iostream>
#include "puyosim.hpp"

namespace PuyoSim {

char test[13][6] = {
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', 'G', '0', '0', '0' },
    { 'B', '0', '0', '0', '0', '0' },
    { 'B', '0', '0', '0', '0', '0' },
    { '0', 'R', '0', '0', '0', '0' },
    { '0', '0', 'R', '0', '0', '0' },
    { 'R', 'R', '0', '0', '0', '0' },
};

Matrix::Matrix(int rows, int cols, int hrows) {
    std::vector<char> noneMatrix(rows * cols, COLOR["NONE"]);
    m_data = noneMatrix;
    m_rows = rows;
    m_cols = cols;
    m_hrows = hrows;
}

char Matrix::colorAt(int x, int y) {
    return m_data[x * m_rows + y];
}

void Matrix::setColor(char p, int x, int y) {
    m_data[x * m_rows + y] = p;
}

void Matrix::setTestChain() {
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 13; ++y) {
            setColor(test[y][x], x, y);
        }
    }
}

void Matrix::print() {
    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            std::cout << colorAt(x, y);
        }
        std::cout << '\n';
    }
}

}