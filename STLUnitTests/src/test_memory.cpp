#include "stdafx.h"

#include <memory>

namespace {
	class ClassSharable : public std::enable_shared_from_this<ClassSharable>
	{ };
}

namespace TestMemory
{
	TEST(test_enable_shared_from_this, try_shared_from_none_shared)
	{
		// given
		auto obj = ClassSharable();

		// then
		ASSERT_THROW(obj.shared_from_this(), std::bad_weak_ptr);		
	}

	TEST(test_enable_shared_from_this, equality)
	{
		// given
		auto obj = std::make_shared<ClassSharable>();

		// when
		auto objShared = obj->shared_from_this();

		// then
		ASSERT_EQ(obj, objShared);
	}

	TEST(test_expired, test0)
	{
		// given
		auto obj = std::make_shared<ClassSharable>();

		// when
		auto weakObj = obj->weak_from_this();

		using namespace testing;

		// then
		ASSERT_THAT(weakObj.expired(), IsFalse());

		// when
		obj.reset();

		// then
		ASSERT_THAT(weakObj.expired(), IsTrue());
	}
}