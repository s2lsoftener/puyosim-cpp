//
//  main.cpp
//  puyosim-cpp
//
//  Created by Phong Tran on 1/8/20.
//

#include <iostream>
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << static_cast<int>(PuyoSim::Color::RED);
    
    PuyoSim::Matrix mat;
    std::cout << mat.data;
    return 0;
}
