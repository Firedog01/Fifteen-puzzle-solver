#include <iostream>
#include "../../lib/puzzle/op_path.h"


std::string op_path::string() const {
    std::stringstream ss;
    for(auto i : this->path) {
        switch(i) {
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
            default:
                ss << "";
                break;
        }
    }
    return ss.str();
}

op_path::op_path(const op_path &old, ops::operators new_op) : path(old.path.size() + 1) {
	if(!old.path.empty()) {
		std::copy(old.path.begin(), old.path.end(), path.begin());
	}
    *(path.end() - 1) = new_op;
}

op_path::op_path(ops::operators op) : path(1) {
	path.at(0) = op;
}

int16_t op_path::get_length() {
	if(path.size() == 1) {
		if(path[0] == ops::NotFound) {
			return -1;
		}
		if(path[0] == ops::None) {
			return 0;
		}
	}
	return path.size();
}
