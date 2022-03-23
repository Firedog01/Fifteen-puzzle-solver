#include <stack>
#include "../lib/strategies.h"

strategies::strategies() {
    board::init_same();
    solved_table = board_handler::new_solved_table(); // to modify solved state pass different function

}


strategies::~strategies() {
    delete[](solved_table);
}

op_path strategies::bfs(state &start_state, ops::operators *order, info_bundle &info) {
    info.processed++;
    info.visited++;

    std::queue<state> open_states;                        /// Q - queue
    std::unordered_map<board, op_path, board_hash> processed_states; /// U - set
    state* cur_state;   // for iteration

    open_states.push(start_state);                     /// Q.enqueue(s)

    while(!open_states.empty()) {                         /// while !Q.isempty():
        cur_state = &open_states.front();                 /// v = Q.dequeue()

        ops::operators* op = order;
        for(int i = 0; i < 4; i++, op++) {                /// for n in neighbours(v):
			auto neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
			if(neighbour == nullptr) { // illegal move or trivial(for example RL or UD)
                continue;
            }
            info.set_max_depth(neighbour->second.path.size());
            if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
                // solution found!
				info.visited++; //xxx not sure if right
                op_path solution = neighbour->second;
                delete neighbour;
                return solution;						/// return success
            }

            /// if !U.has(n):
            ///     Q.enqueue(n)
            ///     U.add(v)
            auto it = processed_states.insert(*neighbour);
            // it.second informs whether insertion was successful
            // processed_states.insert returns std::pair<iterator, bool>
            if(it.second) {
                open_states.push(*neighbour); // copy is created
                info.visited++;
            }
            delete neighbour;
        }
        info.processed++;
        open_states.pop();
    }
    return {1}; // will display size of -1
}

op_path strategies::dfs(state &start_state, ops::operators *order, info_bundle &info) {
    info.processed++;
    info.visited++;
    if(board::same(start_state.first.table.data(), solved_table)) { /// if s is solution:
        return {0};										/// return success
    }
    std::stack<state> open_states;							/// S - stack
    std::unordered_map<board, op_path, board_hash> processed_states; /// T - set

    state* cur_state;   // for iteration

    open_states.push(start_state);						/// S.push(s)
    while(!open_states.empty()) {
		info.processed++;
        cur_state = &open_states.top();						/// v = S.pop()
		auto it = processed_states.insert(*cur_state);
		if(it.second) { // insertion successful
			ops::operators* op = order;
			op += 4;
			for(; op != order; op--) {    					/// for n in neighbours(v).reverse():
				std::cout << "before neighbour\n";
				auto neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
				std::cout << "after neighbour\n";
				if(neighbour == nullptr) { // illegal move or trivial(for example RL or UD)
					continue;
				}
				info.visited++;
				info.set_max_depth(neighbour->second.path.size());
				if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
					// solution found!
					op_path solution = neighbour->second;
					delete neighbour;
					return solution;						/// return success
				}
				open_states.push(*neighbour); 			/// S.push(n)
				delete neighbour;
			}
		}
    }
	return {1};											/// return failure
}

op_path strategies::astr(state &start_state, ops::operators *order, info_bundle &info) {
	info.processed++;
	info.visited++;
	if(board::same(start_state.first.table.data(), solved_table)) { /// if s is solution:
		return {0};										/// return success
	}

//	std::priority_queue<uint16_t, state, > open_states;							/// S - stack
	std::unordered_map<board, op_path, board_hash> processed_states; /// T - set
}

