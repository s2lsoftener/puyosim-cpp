#include <iostream>
#include "puyosim.hpp"

int main() {
	PuyoSim::Matrix mat;
	mat.setTestChain(0);
	mat.print();

	// Calculate the next color pops
	PuyoSim::PuyoPtrGroups nextPops;
	nextPops = PuyoSim::nextColorPops(mat);

	// Calculate the next garbage pops
	PuyoSim::PuyoPtrGroup nextGarbagePops;
	nextGarbagePops = PuyoSim::nextGarbagePops(mat, nextPops);

	// Pop Colored Puyos
	PuyoSim::popColoredPuyos(nextPops);
	// Pop Garbage Puyos
	PuyoSim::popGarbagePuyos(nextGarbagePops);
	
	std::cout<< '\n';
	mat.print();


	std::cout << "Reached.\n";

	return 0;
}
