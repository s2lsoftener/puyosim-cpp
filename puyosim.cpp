#include <iostream>
#include <set>
#include <tuple>
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

Matrix::Matrix(int rows, int cols, int hrows, int puyoToClear, int targetPoint) {
    m_data = std::vector<Puyo>(rows * cols);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Puyo puyo = { COLOR["NONE"], x, y };
            m_data[x * rows + y] = puyo;
        }
    }

    m_rows = rows;
    m_cols = cols;
    m_hrows = hrows;
    m_puyoToClear = puyoToClear;
    m_targetPoint = targetPoint;
}

Puyo* Matrix::puyoAt(int i) {
    return &(m_data[i]);
}

Puyo* Matrix::puyoAt(int x, int y) {
    return &(m_data[x * m_rows + y]);
}

void Matrix::setPuyo(char color, int x, int y) {
    Puyo puyo = { color, x, y };
    m_data[x * m_rows + y] = puyo;
}

size_t Matrix::size() { return m_data.size(); }

void Matrix::setTestChain(int i) {
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 13; ++y) {
            setPuyo(tests[i][y][x], x, y);
        }
    }
}

PuyoPtrGroups nextColorPops(Matrix& mat) {    
    BoolMatrix checked;
    PuyoPtrGroups groups;

    for (int y = 0; y < mat.m_rows; y++) {
        for (int x = 0; x < mat.m_cols; x++) {
            Puyo& currentPuyo = *mat.puyoAt(x, y);

            // If the cell has already been checked, skip
            if (checked.get(x, y)) continue;
            checked.set(true, x, y);

            // If the cell is empty or a garbage, skip
            if (currentPuyo.isNone() || currentPuyo.isGarbage() || currentPuyo.isBlock()) continue;

            std::vector<Puyo*> group;
            group.push_back(mat.puyoAt(x, y));
            int i = 0;

            while (i < static_cast<int>(group.size())) {
                // Check up
                if ((*group[i]).y > mat.m_hrows && !checked.get((*group[i]).x, (*group[i]).y - 1) && (*group[i]).isEqual(*mat.puyoAt((*group[i]).x, (*group[i]).y - 1))) {
                    checked.set(true, (*group[i]).x, (*group[i]).y - 1);
                    group.push_back(mat.puyoAt((*group[i]).x, (*group[i]).y - 1));
                }
                // Check down
                if ((*group[i]).y < mat.m_rows - 1 && !checked.get((*group[i]).x, (*group[i]).y + 1) && (*group[i]).isEqual(*mat.puyoAt((*group[i]).x, (*group[i]).y + 1))) {
                    checked.set(true, (*group[i]).x, (*group[i]).y + 1);
                    group.push_back(mat.puyoAt((*group[i]).x, (*group[i]).y + 1));
                }
                // Check left
                if ((*group[i]).x > 0 && !checked.get((*group[i]).x - 1, (*group[i]).y) && (*group[i]).isEqual(*mat.puyoAt((*group[i]).x - 1, (*group[i]).y))) {
                    checked.set(true, (*group[i]).x - 1, (*group[i]).y);
                    group.push_back(mat.puyoAt((*group[i]).x - 1, (*group[i]).y));
                }
                // Check right
                if ((*group[i]).x < mat.m_cols - 1 && !checked.get((*group[i]).x + 1, (*group[i]).y) && (*group[i]).isEqual(*mat.puyoAt((*group[i]).x + 1, (*group[i]).y))) {
                    checked.set(true, (*group[i]).x + 1, (*group[i]).y);
                    group.push_back(mat.puyoAt((*group[i]).x + 1, (*group[i]).y));
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

PuyoPtrGroup nextGarbagePops(Matrix& mat, PuyoPtrGroups& nextColors) {
    PuyoPtrGroup garbageToPop;

    for (PuyoPtrGroup& group : nextColors) {
        for (Puyo* puyoPtr : group) {
            Puyo& puyo = *puyoPtr;
            
            // Check up
            if (puyo.y > mat.m_hrows && (*mat.puyoAt(puyo.x, puyo.y - 1)).isGarbage()) {
                garbageToPop.push_back(mat.puyoAt(puyo.x, puyo.y - 1));
            }
            // Check down
            if (puyo.y < mat.m_rows - 1 && (*mat.puyoAt(puyo.x, puyo.y + 1)).isGarbage()) {
                garbageToPop.push_back(mat.puyoAt(puyo.x, puyo.y + 1));
            }
            // Check left
            if (puyo.x > 0 && (*mat.puyoAt(puyo.x - 1, puyo.y)).isGarbage()) {
                garbageToPop.push_back(mat.puyoAt(puyo.x - 1, puyo.y));
            }
            // Check right
            if (puyo.x < mat.m_cols - 1 && (*mat.puyoAt(puyo.x + 1, puyo.y)).isGarbage()) {
                garbageToPop.push_back(mat.puyoAt(puyo.x + 1, puyo.y));
            }
        }
    }

    return garbageToPop;
}

void popColoredPuyos(PuyoPtrGroups& nextColors) {
    for (PuyoPtrGroup& group : nextColors) {
        for (Puyo* puyoPtr: group) {
            Puyo& puyo = *puyoPtr;
            puyo.p = COLOR["NONE"];
        }
    }
}

void popGarbagePuyos(PuyoPtrGroup& nextGarbage) {
    for (Puyo* puyoPtr : nextGarbage) {
        Puyo& garbage = *puyoPtr;

        if (garbage.p == COLOR["HARD"]) {
            garbage.p = COLOR["GARBAGE"];
        } else if (garbage.p == COLOR["GARBAGE"]) {
            garbage.p = COLOR["NONE"];
        }
    }
}

void dropPuyos(Matrix& mat) {
    int matSize = static_cast<int>(mat.size());
    for (int colStart = 0; colStart < matSize; colStart += mat.m_rows) {
        int colEnd = colStart + mat.m_rows - 1;

        int i = colEnd - 1;
        while (i >= colStart) {
            // Search for a Puyo
            Puyo& current = *mat.puyoAt(i);

            // If colored or garbage.
            if (!current.isNone() && !current.isBlock()) {
                int r = i;
                int indEmpty = i;
                while (r < colEnd) {
                    r++;
                    Puyo& below = *mat.puyoAt(r);
                    if (below.isNone()) {
                        indEmpty = r;
                    } else {
                        break;
                    }
                }

                if (indEmpty != i) {
                    // Copy current's color to the empty cell
                    Puyo& target = *mat.puyoAt(indEmpty);
                    target.p = current.p;

                    // Make the current Puyo empty
                    current.p = COLOR["NONE"];
                }
            }

            i--;
        }
    }
}

int calcStepScore(Matrix& mat, PuyoPtrGroups& nextColors, int step) {
    std::set<char> colorSet;

    int puyoCleared = 0;
    int groupBonus = 0;
    for (PuyoPtrGroup& group : nextColors) {
        Puyo& puyo = *group[0];

        // Set up color bonus calculation (later)
        colorSet.insert(puyo.p);

        // Total group bonuses
        size_t gInd = group.size() - mat.m_puyoToClear;
        if (gInd >= GROUP_BONUS.size()) {
            groupBonus += GROUP_BONUS.back();
        } else {
            groupBonus += GROUP_BONUS.at(gInd);
        }

        // Total the number of Puyos in each group
        puyoCleared += group.size();
    }

    int colorBonus = COLOR_BONUS[colorSet.size() - 1];
    int chainPower = CHAIN_POWERS[step - 1]; // I don't expect this to exceed 24...
    int puyoClearedMultiplier = puyoCleared * 10;
    int bonusMultipliers = groupBonus + colorBonus + chainPower;
    bonusMultipliers = bonusMultipliers == 0 ? 1 : (bonusMultipliers > 999 ? 999 : bonusMultipliers);

    return puyoClearedMultiplier * bonusMultipliers;
}

int calcChainGarbage(Matrix& mat, int score) {
    // Too lazy to account for leftover nuisance points right now.
    // consider type: std::tuple<int, double>
    return score / mat.m_targetPoint;
}

std::tuple<int, int, int> simulateChain(Matrix& mat) {
    // Simulates the chain, requires mutating the field of
    // the input matrix. Returns the chain length

    int chainLength = 0;
    int score = 0;

    PuyoPtrGroups nextPops;
    nextPops = nextColorPops(mat);

    while (nextPops.size() > 0) {
        // ^^ Do I need to cast size_t to int...?

        chainLength++;

        PuyoPtrGroup nextGarbage;
        nextGarbage = nextGarbagePops(mat, nextPops);

        score += calcStepScore(mat, nextPops, chainLength);

        // Pop Puyos and Garbage, and drop
        popColoredPuyos(nextPops);
        popGarbagePuyos(nextGarbage);
        dropPuyos(mat);

        // Try and find the next pops again
        nextPops = nextColorPops(mat);
    }

    int garbageTotal = calcChainGarbage(mat, score);

    return std::make_tuple(chainLength, score, garbageTotal);
}

using ColorInfo = std::tuple<int, std::vector<char>>;
ColorInfo Matrix::usedColors() {
    std::vector<char> colors;

    for (Puyo puyo : m_data) {
        if (colors.size() == 5) {
            // Found all 5 colors
            break;
        }
        
        if (puyo.isColored()) {
            colors.push_back(puyo.p);
        }
    }
    
    return std::make_tuple(colors.size(), colors);;
}

std::vector<Matrix> permutePlacements(ColorInfo colorInfo) {
    // ...
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