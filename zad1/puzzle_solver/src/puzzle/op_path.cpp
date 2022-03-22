#include "../../lib/puzzle/op_path.h"


std::string op_path::string() const {
    std::stringstream ss;
    for(auto i = this->path.begin(); i != this->path.end(); i++) {
        switch(*i) {
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

op_path::op_path(const op_path &old, ops::operators new_op) : path(old.path.size() + 1) {
//https://stackoverflow.com/questions/39075850/fastest-way-to-copy-a-vector-with-specific-changes-in-c
	if(!old.path.empty()) {
		std::copy(old.path.begin(), old.path.end(), path.begin());
	}
    *(path.end() - 1) = new_op;
}

op_path::op_path(int16_t l): path(l) {
	for(auto i = path.begin(); i != path.end(); i++) {
		*i = ops::Undefined;
	}
}
