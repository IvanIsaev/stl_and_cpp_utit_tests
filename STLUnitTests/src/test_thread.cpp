#include "stdafx.h"

#include <atomic>
#include <thread>
#include <vector>

namespace TestThread
{
	TEST(test_spinlock, test0)
	{
		// given
		class Spinlock
		{
		public:
			void lock()
			{
				while (m_flag.test_and_set());
			}

			void unlock()
			{
				m_flag.clear();
			}

		private:
			std::atomic_flag m_flag = ATOMIC_FLAG_INIT;
		}spinLock;

		auto workOnResource = [&spinLock](int& summ) {
			spinLock.lock();
			++summ;
			spinLock.unlock();
			};

		auto sum = int{ 0 };

		auto t1 = std::thread(workOnResource, std::ref(sum));
		auto t2 = std::thread(workOnResource, std::ref(sum));
		auto t3 = std::thread(workOnResource, std::ref(sum));
		auto t4 = std::thread(workOnResource, std::ref(sum));

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		ASSERT_EQ(sum, 4);
	}

	TEST(test_notify_one, test0)
	{
		// when
		auto vec = std::vector<int>{};
		auto atomicFlag = std::atomic_flag{};
		const auto beginWork = [&]()
			{
				vec.insert(vec.end(), { 0, 1, 2, 3, 4 });
				//std::cout << "Sender: Data prepared." << '\n';
				atomicFlag.test_and_set();
				atomicFlag.notify_one();
			};

		const auto endWork = [&]()
			{
				//std::cout << "Waiter: Waiting for data." << '\n';
				atomicFlag.wait(false);
				vec.insert(vec.end(), { 5, 6, 7, 8, 9 });
				//std::cout << "Waiter: Complete the work." << '\n';
			};

		auto t1 = std::thread{ beginWork };
		auto t2 = std::thread{ endWork };

		t1.join();
		t2.join();

		// then 
		ASSERT_THAT(vec, ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
	}
}