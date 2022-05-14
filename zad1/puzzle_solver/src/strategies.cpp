#include "../lib/strategies.h"

uint16_t (*strategies::heuristic)(state* st, const uint8_t* solved);
typedef std::unordered_map<board, op_path, board_hash>::const_iterator map_iterator;

strategies::strategies() {
    board::init_same();
    solved_table = board_handler::new_solved_table(); // to modify solved state pass different function
}

strategies::~strategies() {
    delete[](solved_table);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* bfs wer 3:
    s - stan początkowy
    if s is solution:
        return success
    Q = queue
    U = set
    Q.enqueue(s)
    while !Q.isempty():
        v = Q.dequeue()
        for n in neighbours(v):
            if n is solution:
                return success
            if !U.has(n):
                Q.enqueue(n)
                U.add(v)
    return failure
 */
op_path strategies::bfs(state &start_state, ops::operators *order, info_bundle &info) const {
    info.visited++;

    std::queue<state> open_states;                        /// Q - queue
    std::unordered_map<board, op_path, board_hash> processed_states; /// U - set
    state* cur_state;   // for iteration
    open_states.push(start_state);                     /// Q.enqueue(s)

    while(!open_states.empty()) {                         /// while !Q.isempty():
        cur_state = &open_states.front();                 /// 	v = Q.dequeue()
        ops::operators* op = order;
        info.processed++;
        for(int i = 0; i < 4; i++, op++) {                /// for n in neighbours(v):
			state* neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
			if(neighbour == nullptr)  // illegal move or trivial(for example RL or UD)
                continue;
            if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
                // solution found!
				info.visited++; //xxx not sure if right
				info.set_max_depth((int)neighbour->second.path.size());
                op_path solution = neighbour->second;
                delete neighbour;
                return solution;							/// return success
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
        open_states.pop();
    }
    return {ops::NotFound}; // will display size of -1
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* dfs nowa implementacja z rozbieżnościami co do rekurencji:
    v - stan początkowy
    G - goal
    dfs(G, s):
        if s is solution:
            return success
        S - lista stanów zamkniętych (stack)
        T - lista stanów otwartych (set)
        S.push(s)
        while !S.empty():
            v = S.pop()
            if !T.has(v):
                T.add(v)
                for n in neghbours(v).reverse():
                    if n is solution:
                        return success
                    S.push(n)
        return failure
 */
op_path strategies::dfs(state &start_state, ops::operators *order, info_bundle &info) const {
    info.visited++;
    if(board::same(start_state.first.table.data(), solved_table))   /// if s is solution:
        return {ops::None};										/// 	return success
    std::stack<state> open_states;									/// S - stack
    std::unordered_map<board, op_path, board_hash> processed_states;/// T - set
	bool isInserted;

    open_states.push(start_state);							/// S.push(s)
    while(!open_states.empty()) {
		info.processed++;
        state cur_state(open_states.top());						/// v = S.pop()
		open_states.pop();										///
		auto it = processed_states.insert(cur_state);
		isInserted = it.second;

		if(!isInserted) {
			if(it.first->second.get_length() > cur_state.second.get_length()) {
				processed_states.erase(it.first); // how long does this execute?
				processed_states.insert(cur_state);
				isInserted = true;
			}
		}
		if(isInserted && cur_state.second.path.size() < DFS_MAX_DEPTH) {
			ops::operators* op = order + 3;
			for(int i = 0; i < 4; i++, op--) {    				/// for n in neighbours(v).reverse():
				state* neighbour = board_handler::new_moved(cur_state, *op); // uses new, must be deleted
				if(neighbour == nullptr)  // illegal move or trivial(for example RL or UD)
					continue;
				info.visited++;
				info.set_max_depth((int) neighbour->second.path.size());
				if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
					op_path solution = neighbour->second;
					delete neighbour;
					return solution;						/// return success
				}

				open_states.push(*neighbour); 			/// S.push(n)
				delete neighbour;
			}
		}
    }
	return {ops::NotFound}; /// return failure
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
astar(G, s):
    if s is solution:
        return success
    P = priority_queue()
    T = set()
    P.insert(s, 0) // z priorytetem zero
    while !P.isempty():
        v = P.pull() // najmniejszy priorytet
        if T.has(v):
            continue
        if v is solution:
            return success
        T.add(v)
        for n in v.neighbours:
        	f = g(n) + h(n)
            P.insert(n, f)
    return failure
 */
op_path strategies::astr(state &start_state, ops::heuristics heur, info_bundle &info) const {
	info.visited++;
	if(board::same(start_state.first.table.data(), solved_table))   	/// if s is solution:
		return {ops::None};											/// 	return success

	if(heur == ops::hamm)
		heuristic = &heuristics::hamming;
	else if(heur == ops::manh)
		heuristic = &heuristics::manhattan;

	std::priority_queue<state_astr, std::vector<state_astr>, astr_compare> open_states;	/// P - priority queue
	std::unordered_map<board, op_path, board_hash> processed_states; 	/// T - set
	ops::operators order[] = {ops::L, ops::R, ops::U, ops::D};
	const state_astr* cur_state;
	ops::operators *op;

	open_states.emplace(start_state, 0); /// P.insert(s, 0)

	while(!open_states.empty()) {
		info.processed++;
		cur_state = &open_states.top(); /// v = P.pull()
		state state_mut(cur_state->s);
		open_states.pop();

		if(board::same(solved_table, state_mut.first.table.data())) { 	/// if n is solution:
			return state_mut.second;									/// 	return success
		}
		auto it = processed_states.insert(state_mut);
		if(!it.second) { 	/// if T.has(v):
							/// 	continue
		} else {
			op = order;
			for(int i = 0; i < 4; i++, op++) {                	/// for n in neighbours(v):
				state* neighbour = board_handler::new_moved(state_mut, *op); // uses new, must be deleted
				if(neighbour == nullptr)  // illegal move or trivial(for example RL or UD)
					continue;
				uint16_t f = heuristic(neighbour, solved_table)
						   + neighbour->second.get_length();
				open_states.emplace(*neighbour, f);				/// 	P.insert(n, f)
				info.visited++;
				delete neighbour;
			}
		}

	}
	return {ops::NotFound}; /// return failure
}

