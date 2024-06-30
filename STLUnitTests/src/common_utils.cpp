#include "stdafx.h"
#include "common_utils.h"

std::tuple<char, int, bool> CommonUtils::getEtalonTuple()
{
	char a = 'a';
	int i = 42;
	bool b = true;

	return std::make_tuple(a, i, b);
}

int CommonUtils::fourtyTwo()
{
	return 42;
}

int CommonUtils::dontIgnoreMe()
{
	return fourtyTwo();
}
