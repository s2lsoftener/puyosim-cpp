#include <iostream>
#include <tuple>
#include "puyosim.hpp"

void testClearing(int i) {
	std::cout << "Test Popping Link" << '\n';
	PuyoSim::Matrix* matPtr = new PuyoSim::Matrix();
	std::cout << "Made matrix" << '\n';
	PuyoSim::Matrix& mat = *matPtr;
	mat.setTestChain(i);
	std::cout << "Set test chain" << '\n';
	mat.print();
	std::cout << "Print chain" << '\n';

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

	delete matPtr;
}

void testDropping() {
	std::cout << "Test gravity, with block Puyos" << '\n';
	PuyoSim::Matrix* matPtr = new PuyoSim::Matrix();
	PuyoSim::Matrix& mat = *matPtr;
	mat.setTestChain(2);
	mat.print();

	PuyoSim::dropPuyos(mat);
	mat.print();

	delete matPtr;
}

void testScoring1() {
	std::cout << "Test calculating a link's score" << '\n';
	PuyoSim::Matrix* matPtr = new PuyoSim::Matrix();
	PuyoSim::Matrix& mat = *matPtr;
	mat.setTestChain(3);
	mat.print();

	// Calculate the next color pops
	PuyoSim::PuyoPtrGroups nextPops;
	nextPops = PuyoSim::nextColorPops(mat);

	// Calculate the next garbage pops
	PuyoSim::PuyoPtrGroup nextGarbagePops;
	nextGarbagePops = PuyoSim::nextGarbagePops(mat, nextPops);

	// Calculate link score
	int score { PuyoSim::calcStepScore(mat, nextPops, 2) };
	int garbageTotal = calcChainGarbage(mat, score);

	std::cout << "Link Score if 2 Chain: " << score << '\n';
	std::cout << "Chain Garbage: " << garbageTotal << '\n';

	delete matPtr;
}

void testFullSimulate() {
	std::cout << "Test simulating full chain" << '\n';
	PuyoSim::Matrix* matPtr = new PuyoSim::Matrix();
	PuyoSim::Matrix& mat = *matPtr;
	mat.setTestChain(0);
	mat.print();
	std::cout << '\n';

	int chainLength;
	int score;
	int garbage;
	std::tie(chainLength, score, garbage) = simulateChain(mat);

	mat.print();
	std::cout << "Chain Length: " << chainLength << '\n';
	std::cout << "Chain Score: " << score << '\n';
	std::cout << "Chain Garbage: " << garbage << '\n';

	delete matPtr;
}


int main() {
	testClearing(0);
	std::cout << "\n\n";

	testClearing(1);
	std::cout << "\n\n";

	testDropping();
	std::cout << "\n\n";

	testScoring1();
	std::cout << "\n\n";

	testFullSimulate();
	std::cout << "\n\n";
	return 0;
}
