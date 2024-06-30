#include "stdafx.h"

#include <variant>

namespace TestVariant
{
	TEST(test_get_if, test0)
	{
		// given
		auto expectedIntValue = 42;
		auto intOrDouble = std::variant<int, double>{ expectedIntValue };

		// when
		auto actualIntValue = std::get_if<int>(&intOrDouble);
		auto actualDoubleValue = std::get_if<double>(&intOrDouble);

		// then
		ASSERT_THAT(*actualIntValue, Eq(expectedIntValue));
		ASSERT_THAT(actualDoubleValue, IsNull());
	}
}