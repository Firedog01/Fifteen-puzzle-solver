#include "extra_info.h"

int extra_info::getLength()
{
	return this->length;
}

int extra_info::getStatesVisited()
{
	return this->statesVisited;
}

int extra_info::getStatesProcessed()
{
	return this->statesProcessed;
}

int extra_info::getRecursionLevel()
{
	return this->recursionLevel;
}

long double extra_info::getExecutionTime()
{
	return this->executionTime;
}

void extra_info::setLength(int length)
{
	this->length = length;
}

void extra_info::setStatesVisited(int statesVisited)
{
	this->statesVisited = statesVisited;
}

void extra_info::setStatesProcessed(int statesProcessed)
{
	this->statesProcessed = statesProcessed;
}

void extra_info::setRecursionLevel(int recursionLevel)
{
	this->recursionLevel = recursionLevel;
}

void extra_info::setExecutionTime(long double executionTime)
{
	this->executionTime = executionTime;
}
