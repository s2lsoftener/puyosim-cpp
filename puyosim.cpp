#include <iostream>
#include "puyo.hpp"
#include "puyosim.hpp"
#include "tests.hpp"

namespace PuyoSim {

BoolMatrix::BoolMatrix(int rows, int cols) {
    m_data = std::vector<bool>(rows * cols, false);
    m_rows = rows;
    m_cols = cols;
}
bool BoolMatrix::get(int x, int y) { return m_data[x * m_rows + y]; }
void BoolMatrix::set(bool b, int x, int y) { m_data[x * m_rows + y] = b; }

Matrix::Matrix(int rows, int cols, int hrows) {
    m_data = std::vector<Puyo>(rows * cols);
    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            Puyo puyo = { COLOR["NONE"], x, y };
            m_data[x * m_rows + y] = puyo;
        }
    }

    m_rows = rows;
    m_cols = cols;
    m_hrows = hrows;
}

Puyo* Matrix::puyoAt(int x, int y) {
    return &(m_data[x * m_rows + y]);
}

void Matrix::setPuyo(char color, int x, int y) {
    Puyo puyo = { color, x, y };
    m_data[x * m_rows + y] = puyo;
}

void Matrix::setTestChain(int i) {
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 13; ++y) {
            setPuyo(tests[i][y][x], x, y);
        }
    }
}

PuyoPtrGroups Matrix::nextColorPops() {    
    BoolMatrix checked;
    PuyoPtrGroups groups;

    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            Puyo& currentPuyo = *puyoAt(x, y);

            // If the cell has already been checked, skip
            if (checked.get(x, y)) continue;
            checked.set(true, x, y);

            // If the cell is empty or a garbage, skip
            if (currentPuyo.p == COLOR["NONE"] || currentPuyo.p == COLOR["GARBAGE"]) continue;

            std::vector<Puyo*> group;
            group.push_back(puyoAt(x, y));
            int i = 0;

            while (i < static_cast<int>(group.size())) {
                // Check up
                if ((*group[i]).y > m_hrows && !checked.get((*group[i]).x, (*group[i]).y - 1) && (*group[i]).isEqual(*puyoAt((*group[i]).x, (*group[i]).y - 1))) {
                    checked.set(true, (*group[i]).x, (*group[i]).y - 1);
                    group.push_back(puyoAt((*group[i]).x, (*group[i]).y - 1));
                }
                // Check down
                if ((*group[i]).y < m_rows - 1 && !checked.get((*group[i]).x, (*group[i]).y + 1) && (*group[i]).isEqual(*puyoAt((*group[i]).x, (*group[i]).y + 1))) {
                    checked.set(true, (*group[i]).x, (*group[i]).y + 1);
                    group.push_back(puyoAt((*group[i]).x, (*group[i]).y + 1));
                }
                // Check left
                if ((*group[i]).x > 0 && !checked.get((*group[i]).x - 1, (*group[i]).y) && (*group[i]).isEqual(*puyoAt((*group[i]).x - 1, (*group[i]).y))) {
                    checked.set(true, (*group[i]).x - 1, (*group[i]).y);
                    group.push_back(puyoAt((*group[i]).x - 1, (*group[i]).y));
                }
                // Check right
                if ((*group[i]).x < m_cols - 1 && !checked.get((*group[i]).x + 1, (*group[i]).y) && (*group[i]).isEqual(*puyoAt((*group[i]).x + 1, (*group[i]).y))) {
                    checked.set(true, (*group[i]).x + 1, (*group[i]).y);
                    group.push_back(puyoAt((*group[i]).x + 1, (*group[i]).y));
                }
                ++i;
            }

            if (static_cast<int>(group.size()) >= 4) {
                groups.push_back(group);
            }

        }
    }

    return groups;
}

PuyoPtrGroup Matrix::nextGarbagePops(PuyoPtrGroups nextColors) {
    PuyoPtrGroup garbageToPop;

    for (PuyoPtrGroup group : nextColors) {
        for (Puyo* puyoPtr : group) {
            Puyo& puyo = *puyoPtr;
            
            // Check up
            if (puyo.y > m_hrows && (*puyoAt(puyo.x, puyo.y - 1)).isGarbage()) {
                garbageToPop.push_back(puyoAt(puyo.x, puyo.y - 1));
            }
            // Check down
            if (puyo.y < m_rows - 1 && (*puyoAt(puyo.x, puyo.y + 1)).isGarbage()) {
                garbageToPop.push_back(puyoAt(puyo.x, puyo.y + 1));
            }
            // Check left
            if (puyo.x > 0 && (*puyoAt(puyo.x - 1, puyo.y)).isGarbage()) {
                garbageToPop.push_back(puyoAt(puyo.x - 1, puyo.y));
            }
            // Check right
            if (puyo.x < m_cols - 1 && (*puyoAt(puyo.x + 1, puyo.y)).isGarbage()) {
                garbageToPop.push_back(puyoAt(puyo.x + 1, puyo.y));
            }
        }
    }

    return garbageToPop;
}

void Matrix::print() {
    std::cout << m_rows << " " << m_cols << '\n';

    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            std::cout << (*puyoAt(x, y)).p;
        }
        std::cout << '\n';
    }
}

}