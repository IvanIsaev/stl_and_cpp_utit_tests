#include "stdafx.h"

#include <cstring>

namespace
{
	class ObjectForCastToString
	{
	public:
		explicit ObjectForCastToString(int value) : m_value(value) {}

		operator std::string() const { return std::to_string(m_value); }

	private:
		int m_value;
	};
}

namespace TestCast
{
	TEST(test_operator_type_cast, test0)
	{
		// given
		const auto obj = ObjectForCastToString{ 42 };

		// then
		ASSERT_EQ(std::string{ obj }, std::string("42"));
	}
}