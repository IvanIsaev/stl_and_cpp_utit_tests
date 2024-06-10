#include "stdafx.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <sstream>


namespace TestIosBase
{
	TEST(test_openmode, test_app)
	{
		// given
		auto hello = std::string{ "Hello" };
		auto stringStream = std::stringstream(hello, std::ios::out | std::ios::app); // app - append	
		stringStream << ", world";
		auto actualStr = std::string{};
		const auto expectedStr = "Hello, world";

		// when
		actualStr = stringStream.str();

		// then
		ASSERT_THAT(actualStr, testing::StrEq(expectedStr));
	}

	TEST(test_openmode, test_binary)
	{
		// given
		auto hello = std::string{ "Hello" };
		auto stringStream = std::stringstream(hello, std::ios::out | std::ios::binary);
		auto actualStr = std::string{};
		const auto expectedStr = "Hello";

		// when
		actualStr = stringStream.str();

		// then
		ASSERT_THAT(actualStr, testing::StrEq(expectedStr));
	}

	TEST(test_openmode, test_in)
	{
		// given
		auto hello = std::string{ "Hello" };
		auto stringStream = std::stringstream(hello, std::ios::in);
		auto actualStr = std::string{};
		const auto expectedStr = "Hello";

		// when
		stringStream >> actualStr;

		// then
		ASSERT_THAT(actualStr, testing::StrEq(expectedStr));
	}

	TEST(test_openmode, test_out)
	{
		// given
		auto hello = std::string{ "Hel_lo" };
		auto stringStream = std::stringstream(hello, std::ios::out);
		auto actualStr = std::string{};
		const auto expectedStr = "bla_lo";
		stringStream << "bla";

		// when
		actualStr = stringStream.str();

		// then
		ASSERT_THAT(actualStr, testing::StrEq(expectedStr));
	}

	TEST(test_openmode, test_trunc)
	{
		// given
		const auto fname = "unique_name.tmp";
		{
			auto fileStream = std::fstream(fname, std::ios::out | std::ios::app);
			fileStream << "Hi";
		}
		{
			auto fileStream = std::fstream(fname, std::ios::out | std::ios::trunc);
			fileStream << "Bla";
		}
		auto actualString = std::string{};

		// when
		std::fstream(fname, std::ios::in) >> actualString;

		// then
		ASSERT_THAT(actualString, testing::StrEq("Bla"));
	}

	TEST(test_openmode, test_ate)
	{
		// given
		auto hello = std::string{ "Hello" };
		{
			auto stringStream = std::ostringstream(hello);
			const auto expectedPos = 0;

			// when
			const auto actualPos = stringStream.tellp();

			// then
			ASSERT_THAT(actualPos, testing::Eq(expectedPos));
		}

		{
			auto stringStream = std::ostringstream(hello, std::ios::ate); // Find end of stream
			const auto expectedPos = 5;

			// when
			const auto actualPos = stringStream.tellp();

			// then
			ASSERT_THAT(actualPos, testing::Eq(expectedPos));
		}
	}

	TEST(test_openmode, test_noreplace) // File will open for writing only if it no exist!
	{
		// given
		const auto fname = "noreplace_fale.tmp";

		if (std::filesystem::exists(fname))
			std::filesystem::remove(fname);

		{ // File will open for writing, because it doesn't exist
			auto fileStream = std::fstream(fname, std::ios::out | std::ios::noreplace);
			ASSERT_TRUE(fileStream.is_open());
			fileStream << "Hi";
		}
		{// File exists, therefore it won't open for write!
			auto fileStream = std::fstream(fname, std::ios::out | std::ios::noreplace);
			ASSERT_FALSE(fileStream.is_open());
			fileStream << "Bla";
		}
	}
}