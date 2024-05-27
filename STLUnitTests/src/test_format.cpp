#include "stdafx.h"

#include <format>

namespace TestFormat
{
	TEST(test_format, test0)
	{
		// given
		const auto hello = "Hello";
		const auto comma = ",";
		const auto space = " ";
		const auto world = "World";
		const auto expectedString = "Hello, World";

		// when
		const auto actualString = std::format("{}{}{}{}", hello, comma, space, world, "smt string");

		//then
		ASSERT_EQ(actualString, expectedString);
	}
}