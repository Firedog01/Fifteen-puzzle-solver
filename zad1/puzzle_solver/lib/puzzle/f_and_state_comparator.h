#ifndef ZAD1_F_AND_STATE_COMPARATOR_H
#define ZAD1_F_AND_STATE_COMPARATOR_H

#include "../includes.h"
#include "../puzzle/board_handler.h"


struct f_and_state_comparator {
	bool operator() (const f_and_state& lhs, const f_and_state& rhs) const
	{
		return (lhs.first > rhs.first);
	}
};


#endif //ZAD1_F_AND_STATE_COMPARATOR_H
