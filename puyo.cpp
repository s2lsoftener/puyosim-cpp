#include "puyo.hpp"

namespace PuyoSim {

bool Puyo::isEqual(Puyo& puyo) {
    return p == puyo.p;
}

bool Puyo::isGarbage() {
    return p == COLOR["GARBAGE"] || p == COLOR["HARD"];
}

bool Puyo::isNone() {
    return p == COLOR["NONE"];
}

bool Puyo::isBlock() {
    return p == COLOR["BLOCK"];
}

}
