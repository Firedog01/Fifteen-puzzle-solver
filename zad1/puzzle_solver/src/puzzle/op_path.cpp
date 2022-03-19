#include "../../lib/puzzle/op_path.h"

bool op_path::operator==(const op_path &other) const {
    ops::operators *thisp = this->path,
                   *othrp = other.path;

    bool retVal = true;
    for(uint8_t i = 0; i < this->len; i++, thisp++, othrp++) {
        if(*thisp ^ *othrp) {
            retVal = false;
        }
    }
    return retVal;
}

std::string op_path::toString() const {
    std::stringstream ss;
    auto ops = this->path;
    for(int i = 0; i < this->len; i++, ops++) {
        switch(*ops) {
            case ops::L:
                ss << "L";
                break;
            case ops::R:
                ss << "R";
                break;
            case ops::D:
                ss << "D";
                break;
            case ops::U:
                ss << "U";
                break;
            case ops::Undefined:
                ss << "!";
                break;
        }
    }
    ss << "\n";
    return ss.str();
}

op_path::op_path(const op_path &old, ops::operators new_op) : len(old.len + 1), lastOp(new_op) {
    path = new ops::operators[len];
    std::copy(old.path, old.path + len, path);
    path[len - 1] = new_op;
}
