#ifndef ZAD1_INCLUDES_H
#define ZAD1_INCLUDES_H

#include <cstdint>
#include <memory>

// todo: rename this namespace
namespace ops {
		// explicit for readability, look inside board_handler
    enum operators: uint8_t {L = 0b00, R = 0b01, U = 0b10, D = 0b11,
			Undefined = 0b1000, Zero = 0b1001};
    enum heuristics {hamm, manh, error};
}
class board;
class op_path;
typedef std::pair<board, op_path> state;
typedef std::pair<uint16_t, state> f_and_state; // i dont like that

#endif //ZAD1_INCLUDES_H
