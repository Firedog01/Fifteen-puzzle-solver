#ifndef ZAD1_INCLUDES_H
#define ZAD1_INCLUDES_H

#include <cstdint>
#include <memory>

// todo: rename this namespace
namespace ops {
    enum operators: int8_t {
		L = 0b00,
		R = 0b01,
		U = 0b10,
		D = 0b11,
		None, NotFound
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
typedef std::pair<uint16_t, state> f_and_state; // i dont like that


#endif //ZAD1_INCLUDES_H
