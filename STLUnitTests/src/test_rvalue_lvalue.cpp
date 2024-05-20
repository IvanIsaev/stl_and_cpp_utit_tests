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
		ASSERT_EQ(foo(&c), 1); // ������, ��� � foo ���������� rvalue ������ �� ���������
		ASSERT_EQ(foo(cD), 2); // ������, ��� � foo ���������� lvalue ������ �� ���������
	}
}