#include "common_utils.h"

std::tuple<char, int, bool> CommonUtils::getEtalonTuple()
{
	char a = 'a';
	int i = 42;
	bool b = true;

	return std::make_tuple(a, i, b);
}
