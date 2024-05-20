#include "stdafx.h"

#include <memory>

namespace {
	class ClassSharable : public std::enable_shared_from_this<ClassSharable>
	{
		std::shared_ptr<ClassSharable> getShared()
		{
			return shared_from_this();
		}

		std::weak_ptr<ClassSharable> getWeak()
		{
			return weak_from_this();
		}
	};
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
}