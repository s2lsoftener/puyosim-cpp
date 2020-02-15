#include <iostream>
#include "puyosim.hpp"

int main() {
    PuyoSim::Matrix mat;
    mat.setTestChain();
    mat.print();
    // std::cout << "Checking pops..." << '\n';
    // PuyoSim::PuyoGroups nextColorPops = mat.nextColorPops();
    // std::cout << "Garbage To Pop: " << '\n';
    // PuyoSim::PuyoGroup nextGarbage = mat.nextGarbagePops(nextColorPops);
    // for (PuyoSim::Puyo garbage : nextGarbage) {
    //     std::cout << garbage.p << " ~ x:" << garbage.x << " y:" << garbage.y << '\n';
    // }
    return 0;
}
