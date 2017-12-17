#pragma once
#include <list>
#include <vector>

using namespace std;

class LogicPattern
{
public:
	LogicPattern();
	~LogicPattern();
	int Add(int);
	int Remove(int);
	int to_Array(int*,int&);
	int get_length();
	vector<int> get_vector();
	int get_at(int i);

private:
	vector<int> _pI_pattern;
};
