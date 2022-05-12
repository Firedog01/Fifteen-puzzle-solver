#ifndef ZAD1_INCLUDES_H
#define ZAD1_INCLUDES_H

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

// todo: rename this namespace
namespace ops {
    enum operators: int8_t {
		L = 0b00,
		R = 0b01,
		U = 0b10,
		D = 0b11,
		None = 0b1000, NotFound = 0b1001
	};
    enum heuristics {
		hamm,
		manh,
		error
	};
}
class board;
class op_path;
typedef std::pair<board, op_path> state;

#endif //ZAD1_INCLUDES_H
