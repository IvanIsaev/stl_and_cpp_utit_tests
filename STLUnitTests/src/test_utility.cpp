#include "stdafx.h"

#include <utility>
#include <vector>

TEST(test_exchange, test0)
{
	// given
	auto v = std::vector<int>{};
	auto vectorToExchange = { 1, 2, 3, 4 };
	const auto copyOfVectorToExchange = vectorToExchange;
	const auto expectedFibbonaci10Value = 55;

	// when
	std::exchange(v, std::move(vectorToExchange));
	auto actualFibbonaci = int{ 0 };
	for (auto i = int{0}, b = int{1}; i < 10; actualFibbonaci = std::exchange(b, actualFibbonaci + b), ++i);

	// then
	ASSERT_THAT(v, copyOfVectorToExchange);
	ASSERT_EQ(actualFibbonaci, expectedFibbonaci10Value);
}