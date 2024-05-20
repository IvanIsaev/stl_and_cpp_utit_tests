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

namespace TestAtomic
{
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

	TEST(test_load, test0)
	{
		// given
		auto atomicInt = std::atomic{ 42 };

		// then
		ASSERT_EQ(atomicInt.load(), 42);
		ASSERT_EQ(atomicInt, 42);
	}

	TEST(test_store, test0)
	{
		// given
		auto atomicInt = std::atomic{ 42 };
		auto value = int{ 43 };

		// when
		atomicInt.store(value);

		// then
		ASSERT_EQ(atomicInt, value);
	}

	TEST(test_exchange, test0)
	{
		// given
		auto oldValue = int{ 42 };
		auto atomicInt = std::atomic{ oldValue };
		auto newValue = int{ 24 };

		// then
		ASSERT_EQ(atomicInt.exchange(newValue), oldValue);
		ASSERT_EQ(atomicInt, newValue);
	}

	TEST(test_compare_exchange_strong, test0)
	{}

	TEST(test_compare_exchange_weak, test0)
	{}

	TEST(test_wait_and_notify, test0)
	{
		// when
		auto vec = std::vector<int>{};
		auto atomicInt = std::atomic{0};
		const auto beginWork = [&]()
			{
				vec.insert(vec.end(), { 0, 1, 2, 3, 4 });
				//std::cout << "Sender: Data prepared." << '\n';
				atomicInt.store(vec.size());
				atomicInt.notify_one();
			};

		const auto endWork = [&]()
			{
				//std::cout << "Waiter: Waiting for data." << '\n';
				atomicInt.wait(0);
				vec.insert(vec.end(), { 5, 6, 7, 8, 9 });
				//std::cout << "Waiter: Complete the work." << '\n';
			};

		auto t1 = std::thread{ beginWork };
		auto t2 = std::thread{ endWork };

		t1.join();
		t2.join();

		// then 
		ASSERT_THAT(vec, testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
	}
}