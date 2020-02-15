#include <iostream>
#include "puyosim.hpp"

int main() {
    PuyoSim::Matrix mat;
	mat.setTestChain(0);
	mat.print();

    // Calculate the next color and garbage pops
	PuyoSim::PuyoPtrGroups nextPops = mat.nextColorPops();
	PuyoSim::PuyoPtrGroup nextGarbage = mat.nextGarbagePops(nextPops);

	for (auto garbage : nextGarbage) {
		std::cout << (*garbage).p;
	}

	return 0;
}
