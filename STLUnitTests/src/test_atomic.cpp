#include "stdafx.h"

#include <atomic>
#include <cstring>

namespace 
{
	struct NotLockFree
	{
		int a[100];
	};
}

TEST(test_is_lock_free, test0)
{
	// given
	std::atomic_flag flag; // always lock-free
	std::atomic<double> atomicDouble;
	std::atomic<int> atomicInt;
	std::atomic<NotLockFree> atomicNotLockFree;

	// then
	ASSERT_TRUE(atomicDouble.is_lock_free());
	ASSERT_TRUE(atomicInt.is_lock_free());
	ASSERT_FALSE(atomicNotLockFree.is_lock_free());
}

TEST(test_is_always_lock_free, test0)
{
	// then
	ASSERT_TRUE(std::atomic<double>::is_always_lock_free);
	ASSERT_TRUE(std::atomic<int>::is_always_lock_free);
}