#include "stdafx.h"
#include <cstddef>

namespace
{
}

namespace TestCstddef
{
	TEST(test_cstddef, test0)
	{
		// given
		struct T
		{
			char c = 0;
			double d = 0.1;
			int i = 2;
			short s = 3;
		};
		
		// then
		ASSERT_THAT(offsetof(T, c), Eq(0));
		ASSERT_THAT(offsetof(T, d), Eq(8));
		ASSERT_THAT(offsetof(T, i), Eq(16));
		ASSERT_THAT(offsetof(T, s), Eq(20));
	}
}