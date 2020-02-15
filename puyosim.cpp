#include <iostream>
#include "puyosim.hpp"

namespace PuyoSim {

char test[13][6] = {
    { '0', '0', '0', '0', '0', '0' },
    { '0', '0', '0', '0', '0', '0' },
    { '0', '0', '0', '0', '0', '0' },
    { '0', '0', '0', '0', '0', 'G' },
    { '0', '0', '0', '0', '0', 'G' },
    { '0', '0', '0', '0', 'G', 'G' },
    { 'G', 'R', 'B', '0', 'G', 'J' },
    { 'R', 'B', 'B', '0', 'J', 'J' },
    { 'R', 'R', 'B', '0', 'J', 'J' },
    { 'J', 'J', 'J', 'P', 'J', 'Y' },
    { 'G', 'R', 'B', 'J', 'Y', 'Y' },
    { 'G', 'G', 'R', 'B', 'P', 'P' },
    { 'R', 'R', 'B', 'B', 'P', 'Y' },
};

bool Puyo::isEqual(Puyo& puyo) {
    return p == puyo.p;
}

bool Puyo::isGarbage() {
    return p == COLOR["GARBAGE"] || p == COLOR["HARD"];
}

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

void Matrix::setTestChain() {
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 13; ++y) {
            setPuyo(test[y][x], x, y);
        }
    }
}

PuyoGroups Matrix::nextColorPops() {
    BoolMatrix checked;
    PuyoGroups groups;

    for (int y = 0; y < m_rows; y++) {
        for (int x = 0; x < m_cols; x++) {
            Puyo& currentPuyo = *puyoAt(x, y);
            
            // If the cell has already been checked, skip
            if (checked.get(x, y)) continue;
            checked.set(true, x, y);

            // If the cell is empty or a garbage, skip
            if (currentPuyo.p == COLOR["NONE"] || currentPuyo.p == COLOR["GARBAGE"]) continue;

            std::vector<Puyo> group;
            group.push_back(*puyoAt(x, y));
            int i = 0;

            while (i < static_cast<int>(group.size())) {
                // Check up
                if (group[i].y > m_hrows && !checked.get(group[i].x, group[i].y-1) && group[i].isEqual(*puyoAt(group[i].x, group[i].y-1))) {
                    checked.set(true, group[i].x, group[i].y-1);
                    group.push_back(*puyoAt(group[i].x, group[i].y-1));
                }
                // Check down
                if (group[i].y < m_rows - 1 && !checked.get(group[i].x, group[i].y+1) && group[i].isEqual(*puyoAt(group[i].x, group[i].y+1))) {
                    checked.set(true, group[i].x, group[i].y+1);
                    group.push_back(*puyoAt(group[i].x, group[i].y+1));
                }
                // Check left
                if (group[i].x > 0 && !checked.get(group[i].x-1, group[i].y) && group[i].isEqual(*puyoAt(group[i].x-1, group[i].y))) {
                    checked.set(true, group[i].x-1, group[i].y);
                    group.push_back(*puyoAt(group[i].x-1, group[i].y));
                }
                // Check right
                if (group[i].x < m_cols - 1 && !checked.get(group[i].x+1, group[i].y) && group[i].isEqual(*puyoAt(group[i].x+1, group[i].y))) {
                    checked.set(true, group[i].x+1, group[i].y);
                    group.push_back(*puyoAt(group[i].x+1, group[i].y));
                }
                ++i;
            }

            if (static_cast<int>(group.size()) >= 4) {
                groups.push_back(group);
            }

        }
    }

    // Print which groups need to pop
    for (PuyoGroup group : groups) {
        for (Puyo puyo : group) {
            std::cout << puyo.p;
        }
        std::cout << '\n';
    }

    return groups;
}

// PuyoGroup Matrix::nextGarbagePops(PuyoGroups& coloredPuyo) {
//     PuyoGroup garbageToPop;
    
//     for (PuyoGroup group : coloredPuyo) {
//         for (Puyo puyo : group) {
//             std::cout << puyo.p << " " << puyo.x << " " << puyo.y << '\n';
            
//             // Check up
//             if (puyo.y > m_hrows && (*puyoAt(puyo.x, puyo.y - 1)).isGarbage()) {
//                 garbageToPop.push_back(*puyoAt(puyo.x, puyo.y - 1));
//             }
//             // Check down
//             if (puyo.y < m_rows - 1 && (*puyoAt(puyo.x, puyo.y + 1)).isGarbage()) {
//                 garbageToPop.push_back(*puyoAt(puyo.x, puyo.y + 1));
//             }
//             // Check left
//             if (puyo.x > 0 && (*puyoAt(puyo.x - 1, puyo.y)).isGarbage()) {
//                 garbageToPop.push_back(*puyoAt(puyo.x - 1, puyo.y));
//             }
//             // Check right
//             if (puyo.x < m_cols - 1 && (*puyoAt(puyo.x + 1, puyo.y)).isGarbage()) {
//                 garbageToPop.push_back(*puyoAt(puyo.x + 1, puyo.y));
//             }
//         }
//     }

//     return garbageToPop;
// }

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