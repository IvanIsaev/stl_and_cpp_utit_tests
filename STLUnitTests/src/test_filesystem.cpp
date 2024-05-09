#include "stdafx.h"

#include <filesystem>

// Gives prefered directory separator for win or for linux (\\ or /)
TEST(test_make_preffered, test0)
{
	// given
	const auto winPath = "this\\is\\path";
	const auto linuxPath = "this/is/path";

	// when
	auto preferedLinuxPath = std::filesystem::path(linuxPath).make_preferred();
	auto preferedWinPath = std::filesystem::path(winPath).make_preferred();

	// then
#ifdef _WIN32
	ASSERT_EQ(preferedLinuxPath, winPath);
	ASSERT_EQ(preferedWinPath, winPath);
#elif __linux__
	ASSERT_EQ(preferedLinuxPath, linuxPath);
	ASSERT_EQ(preferedWinPath, linuxPath);
#endif
}