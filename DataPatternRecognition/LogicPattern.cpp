#include "LogicPattern.hpp"

LogicPattern::LogicPattern()
{
}

LogicPattern::~LogicPattern()
{
}

int LogicPattern::Add(int i)
{
	_pI_pattern.push_back(i);
	return EXIT_SUCCESS;
}

int LogicPattern::Remove(int i)
{
	for (int iterator = 0; iterator<_pI_pattern.capacity(); iterator++)
	{
		if (iterator == i)
		{
			_pI_pattern.erase(_pI_pattern.begin() + iterator);
		}
	}
	return EXIT_FAILURE;
}

//Don't leak the memory!
int LogicPattern::to_Array(int* i, int& c)
{
	c = _pI_pattern.capacity();
	i = new int(c);
	if (i != NULL)
	{
		for (size_t j = 0; j < c; j++)
		{
			i[j] = _pI_pattern.at(j);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int LogicPattern::get_length()
{
	return _pI_pattern.capacity();
}

int LogicPattern::get_at(int i)
{
	return _pI_pattern.at(i);
}