#ifndef ZAD1_OP_PATH_H
#define ZAD1_OP_PATH_H
#include <cstdint>
#include <string>
#include <sstream>
#include "../includes.h"

// value of hashmap
struct op_path {
    ops::operators *path;
    int16_t len;
    ops::operators last_op;

    op_path() : len(0), path(nullptr), last_op(ops::Undefined) {}
    op_path(const int16_t l) : len(l), path(nullptr), last_op(ops::Undefined) {} // for setting -1
    op_path(const op_path& old, ops::operators new_op); // create moved
    std::string string() const; // called once for program, therefore returning by value
    bool operator==(const op_path &other) const;
};


#endif //ZAD1_OP_PATH_H
