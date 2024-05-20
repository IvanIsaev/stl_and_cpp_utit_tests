#include "stdafx.h"

#include "common_utils.h"

#include <tuple>

namespace TestTuple
{
	TEST(test_tie, test0)
	{
		// given
		auto c = char{};
		auto i = int{};
		auto b = bool{};

		// when
		std::tie(c, i, b) = CommonUtils::getEtalonTuple();
		const auto expected = CommonUtils::getEtalonTuple();

		// then
		ASSERT_EQ(c, std::get<0>(expected));
		ASSERT_EQ(i, std::get<1>(expected));
		ASSERT_EQ(b, std::get<2>(expected));
	}

	TEST(test_tie, test1)
	{
		// given

		// when
		auto [c, i, b] = CommonUtils::getEtalonTuple();
		const auto expected = CommonUtils::getEtalonTuple();

		// then
		ASSERT_EQ(c, std::get<0>(expected));
		ASSERT_EQ(i, std::get<1>(expected));
		ASSERT_EQ(b, std::get<2>(expected));
	}

	TEST(test_tie, test2)
	{
		// given
		auto i = int{};
		auto b = bool{};

		// when
		std::tie(std::ignore, i, b) = CommonUtils::getEtalonTuple();
		const auto expected = CommonUtils::getEtalonTuple();

		// then
		ASSERT_EQ(i, std::get<1>(expected));
		ASSERT_EQ(b, std::get<2>(expected));
	}

	TEST(test_tie, test3)
	{
		// given
		auto pairForPast = std::make_pair(1, "Hello");

		// when
		auto mapa = std::map<int, std::string>{};
		auto [itElem, succes] = mapa.insert(pairForPast);


		// then
		ASSERT_TRUE(succes);
		ASSERT_EQ(*itElem, pairForPast);
	}

	TEST(test_tie, test4)
	{
		// given
		auto aExpected = 'a';
		auto iExpected = 123;
		auto bExpected = true;


		// when
		auto [a, i, b] = std::tuple('a', 123, true);

		// then
		ASSERT_EQ(a, aExpected);
		ASSERT_EQ(i, iExpected);
		ASSERT_EQ(b, bExpected);
	}

	TEST(test_tie, test5)
	{
		// given
		auto sum = 0;

		// when
		for (auto [i, end] = std::pair(1, 10); i < end; ++i)
			sum += i;

		// then
		ASSERT_EQ(sum, 45);
	}

	TEST(test_tie, test6)
	{
		// given

		// when

		// then
		if (auto [a, b] = std::tuple(1, 2); a < b)
			ASSERT_TRUE(a < b);
	}
}