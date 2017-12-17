#include "DataPatternRecognizer.hpp"

void main()
{
	DataPatternRecognizer rec(1,5);
	rec.AddFile("test.txt");
	rec.AddLogicPattern();
	rec.AddLogicPatternItem(0);
	rec.AddLogicPattern();
	rec.AddLogicPatternItem(1);
	rec.AddLogicPattern();
	rec.AddLogicPatternItem(2);
	rec.AddLogicPatternItem(3);
	rec.AddLogicPattern();
	rec.AddLogicPatternItem(4);
	rec.Start();
}