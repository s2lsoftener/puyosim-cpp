#ifndef PUYO_HPP_2020_02
#define PUYO_HPP_2020_02

#include <vector>
#include <map>
#include <string>

namespace PuyoSim {

inline std::map<std::string, char> COLOR = {
    {"NONE", '0'},
    {"RED", 'R'},
    {"GREEN", 'G'},
    {"BLUE", 'B'},
    {"YELLOW", 'Y'},
    {"PURPLE", 'P'},
    {"GARBAGE", 'J'},
    {"HARD", 'H'},
    {"BLOCK", 'L'}
};

class Puyo {
public:
    char p;
    int x;
    int y;

    bool isEqual(Puyo& puyo);
    bool isGarbage();
    bool isNone();
    bool isBlock();
};

using PuyoPtrGroup = std::vector<Puyo*>;
using PuyoPtrGroups = std::vector<std::vector<Puyo*>>;

}

#endif /* PUYO_HPP */