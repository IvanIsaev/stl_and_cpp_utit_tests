#include "stdafx.h"

namespace {
	int foo(char*&& val) { return 1; }
	int foo(char*& val) { return 2; }
}

namespace TestRvalueLvalue
{
	TEST(TestRefsToPointer, test0)
	{
		// when
		char c = 'a';
		char* cD = &c;

		// then
		ASSERT_EQ(foo(&c), 1); // ѕотому, что в foo передаетс€ rvalue ссылка на указатель
		ASSERT_EQ(foo(cD), 2); // ѕотому, что в foo передаетс€ lvalue ссылка на указатель
	}
}