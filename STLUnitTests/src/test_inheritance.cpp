#include "stdafx.h"

namespace TestInheritance {

	TEST(test_diamond_inheritance, test0)
	{
		class A
		{
		public:
			void foo()
			{

			}
		};

		class B : virtual public A
		{

		};

		class C : virtual public A
		{

		};

		class D : public B, public C
		{
			void doo()
			{
				foo();
			}
		};
	}	

	TEST(test_inheritance, test0)
	{
		// При наследовании с разными типами (public, protected, private) класс потомок получает доступ к полям базового класса следующим образом
		// public:
		// public -> public
		// protected -> protected
		// private -> private
		// 
		// protected:
		// public -> protected
		// protected -> protected
		// private -> private
		// 
		// private:
		// public -> private
		// protected -> private
		// private -> private
	}

	TEST(test_Public_Morozov, test0)
	{
		class Papa
		{
		protected:
			int getMoney() { return 1000000; }
		};

		class Public_Morozov : public Papa
		{
		public:
			using Papa::getMoney; // Теперь метод getMoney() стал публичным... вот так
		};

		Public_Morozov pb;
		ASSERT_THAT(pb.getMoney(), testing::Eq(1000000));
	}
}