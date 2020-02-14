//
//  matrix.hpp
//  puyosim-cpp
//
//  Created by Phong Tran on 1/8/20.
//

#ifndef matrix_hpp
#define matrix_hpp

namespace PuyoSim {

enum class Color {
    NONE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    GARBAGE
};

const int DEFAULT_COLS { 6 };
const int DEFAULT_ROWS { 13 };

class Matrix {
public:
    int data[DEFAULT_COLS][DEFAULT_ROWS];
    Matrix() {}
    
    void setData(int newData[DEFAULT_COLS][DEFAULT_ROWS]);
};

}

#endif /* matrix_hpp */
