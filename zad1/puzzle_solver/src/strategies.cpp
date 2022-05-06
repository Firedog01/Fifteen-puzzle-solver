#include "../lib/strategies.h"
#include "../lib/puzzle/heuristics.h"
#include "../lib/util/astr_priority_queue.h"

uint16_t (*strategies::heuristic)(state* st, uint8_t* solved);

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
        for(int i = 0; i < 4; i++, op++) {                /// for n in neighbours(v):
			state* neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
			if(neighbour == nullptr)  // illegal move or trivial(for example RL or UD)
                continue;
            info.set_max_depth((int)neighbour->second.path.size());
            if(board::same(solved_table, neighbour->first.table.data())) { /// if n is solution:
                // solution found!
				info.visited++; //xxx not sure if right
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
        info.processed++;
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
		if(it.first->second.get_length() > cur_state.second.get_length()) {
			processed_states.erase(it.first); // how long does this execute?
			processed_states.insert(cur_state);
//			it.first->second = cur_state.second;
			isInserted = true;
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
/* astar(G, s):
    if s is solution:
        return success
    P = priority_queue()
    T = set()
    P.insert(s, 0) // z priorytetem zero
    while !P.isempty():
        v = P.pull() // najmniejszy priorytet
        if v is solution:
            return success
        T.add(v)
        for n in v.neighbours:
            if !T.has(n):
                f = g(n) + h(n)
                if !P.has(n):
                    P.insert(n, f)
                else:
                    if P.priority(n) > f:
                        P.update(n, f) // zastąp
    return failure
 */
op_path strategies::astr(state &start_state, ops::heuristics* heur, info_bundle &info) const {
	info.visited++;
	if(board::same(start_state.first.table.data(), solved_table))   /// if s is solution:
		return {ops::None};										/// 	return success

	if(*heur == ops::hamm)
		heuristic = &heuristics::hamming;
	else if(*heur == ops::manh)
		heuristic = &heuristics::manhattan;
	std::vector<std::unordered_map<board, op_path, board_hash>> open_st(OPEN_STATES_SIZE); 	/// P - priority queue
	uint8_t first_no_empty_idx = 0;
	uint16_t cur_size = OPEN_STATES_SIZE;
	for (uint16_t j = 0; j < cur_size; j++) // xxx nie jestem pewien czy to jest potrzebne ==============================================
		open_st.emplace_back();
	std::unordered_map<board, op_path, board_hash> processed_states; 							/// T - set
	ops::operators order[] = {ops::L, ops::R, ops::U, ops::D};
	state_map_iterator cur_state;
	ops::operators *op;

	open_st.at(0).insert(start_state);							/// P.insert(s, 0)
	while(first_no_empty_idx != cur_size) {								/// while !P.isempty():
		info.processed++;
		cur_state = open_st.at(first_no_empty_idx).begin(); 			/// 	v = P.pull()
		if(board::same(cur_state->first.table.data(), solved_table)) 	///		if v is solution:
			return cur_state->second;									///			return success
		processed_states.insert(*cur_state);							/// 	T.add(v)
		op = order;
		for(uint8_t i = 0; i < 4; i++, op++) {							/// 	for n in v.neighbours:
			auto neighbour = board_handler::new_moved(*cur_state, *op); // uses new, must be deleted
			if(neighbour == nullptr)  // illegal move or trivial(for example RL or UD)
				continue;
			info.visited++;
			uint16_t priority = neighbour->second.get_length();				///
			priority += heuristic(neighbour, solved_table);					/// f = g(n) + h(n)
			if(cur_size < priority) { // resize vector if necessary
				uint16_t dif = priority - cur_size + 1;
				for (uint16_t j = 0; j < dif; j++)
					open_st.emplace_back();
			}

			/// if !P.has(n):
			/// 	P.insert(n, f)
			/// else:
			///     if P.priority(n) > f:
			///         P.update(n, f)
			auto it = open_st.at(priority).insert(*neighbour);
			if(it.second) { // insertion successful
				for(uint16_t j = priority; j < cur_size; j++) { // delete all same state
					auto it_j = open_st.at(j).find(neighbour->first);
					if(it_j != open_st.at(j).end())
						open_st.at(j).erase(it_j);
				}
			}
			delete neighbour;
		}
		open_st.at(first_no_empty_idx).erase(cur_state);
		first_no_empty_idx = 0;
		while(open_st.at(first_no_empty_idx).empty()) // mb slow
			first_no_empty_idx++;
	}

	return {ops::NotFound};
}

