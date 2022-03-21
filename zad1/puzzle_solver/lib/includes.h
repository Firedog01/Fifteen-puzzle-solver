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
typedef std::shared_ptr<uint8_t[]> tbl_ptr;
//typedef bool (*same_func)(uint8_t* first, uint8_t* second);
//same_func same;

#endif //ZAD1_INCLUDES_H
