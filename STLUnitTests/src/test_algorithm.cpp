#include "stdafx.h"

#include <algorithm>

namespace TestAlgorithm
{
	TEST(test_clamp, test0)
	{
		// given
		const auto l = 3.5;
		const auto h = 4.0;

		// when
		auto cmp = 3.1;
		// then
		ASSERT_DOUBLE_EQ(l, std::clamp(cmp, l, h));

		// when
		cmp = 3.6;
		// then
		ASSERT_DOUBLE_EQ(cmp, std::clamp(cmp, l, h));

		// when
		cmp = 4.6;
		// then
		ASSERT_DOUBLE_EQ(h, std::clamp(cmp, l, h));
	}
}