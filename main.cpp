#include <iostream>
#include "puyosim.hpp"

int main() {
    PuyoSim::Matrix mat;
	mat.setTestChain();
	mat.print();

	PuyoSim::PuyoGroups nextColors = mat.nextColorPops();
	PuyoSim::PuyoGroup nextGarbages = mat.nextGarbagePops(nextColors);

    std::cout << "ok\n";
	for (auto garbage : nextGarbages) {
		std::cout << garbage.p;
	}

	return 0;
}
