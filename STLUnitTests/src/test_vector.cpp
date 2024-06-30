#include "stdafx.h"

#include <vector>

namespace TestVector
{
	TEST(test_push_back, test0)
	{
		// given
		auto value = 42;
		std::vector v = { value };
		
		// when
		v.push_back(v.front()); // May by UB bcs reallocation		
		
		// then
		ASSERT_THAT(v.back(), Eq(value));
	}
}