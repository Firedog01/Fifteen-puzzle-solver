#pragma once

class extra_info
{
	int length;
	int statesVisited;
	int statesProcessed;
	int recursionLevel;
	long double executionTime;

public:
	int getLength();
	int getStatesVisited();
	int getStatesProcessed();
	int getRecursionLevel();
	long double getExecutionTime();

	void setLength(int length);
	void setStatesVisited(int statesVisited);
	void setStatesProcessed(int statesProcessed);
	void setRecursionLevel(int recursionLevel);
	void setExecutionTime(long double executionTime);
};

