#ifndef ZAD1_OP_PATH_H
#define ZAD1_OP_PATH_H
#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include "../includes.h"

// value of hashmap
struct op_path {
    std::vector<ops::operators> path;

//    op_path(int16_t l);
    op_path(const op_path& old, ops::operators new_op); // create moved
	op_path(ops::operators op);
	op_path() = default;

	int16_t get_length();
    std::string string() const; // called once for program, therefore returning by value
};


#endif //ZAD1_OP_PATH_H
