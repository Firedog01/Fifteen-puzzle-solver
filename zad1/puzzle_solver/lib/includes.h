#ifndef ZAD1_INCLUDES_H
#define ZAD1_INCLUDES_H

#include <cstdint>
#include <memory>

// todo: rename this namespace
namespace ops {
    enum operators {L, R, U, D, Undefined};
    enum heuristics {hamm, manh, error};
}
class board;
class op_path;
typedef std::pair<board, op_path> state;

#endif //ZAD1_INCLUDES_H
