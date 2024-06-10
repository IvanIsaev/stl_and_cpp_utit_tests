#include "stdafx.h"

namespace TestOldSupport
{
	TEST(bit_field, test0)
	{
		// given
		struct BitField
		{
			unsigned int bf : 3;
		}obj;
		obj.bf = 6;

		// when
		obj.bf++;
		// then
		ASSERT_EQ(obj.bf, 7);

		// when
		obj.bf++; // Value 8 doesn't fit for bit field
		// then
		ASSERT_EQ(obj.bf, 0);

		// when
		obj.bf = 8; // Value 8 doesn't fit for bit field
		// then
		ASSERT_EQ(obj.bf, 0);
	}

	TEST(bit_field, test1)
	{
		// given
		struct BitField
		{
			int bf : 5;
			int bf1 : 11;
		}obj;

		// then
		//ASSERT_EQ(&obj.bf, &obj.bf1); //Taking the address of a bit fild is not allowed
	}

	TEST(check_object_size, test0)
	{
		using namespace testing;

		// when
		struct S0
		{
			uint8_t a;
		};
		// then
		ASSERT_THAT(sizeof(S0), Eq(1));

		// when
		struct S1
		{
			uint16_t a;
		};
		// then
		ASSERT_THAT(sizeof(S1), Eq(2));

		// when
		struct S2
		{
			uint32_t a;
		};
		// then
		ASSERT_THAT(sizeof(S2), Eq(4));

		// when
		struct S3 // Двубайтные типы данных выравниваются по адресам, кратным 2
		{
			uint8_t a0; // 1 byte
			// 1 empty byte
			uint16_t a1; // 2 bytes
		};
		// then
		ASSERT_THAT(sizeof(S3), Eq(4));

		// when
		struct S4 // Четырехбайтные типы данных выравниваются по адресам, кратным 4
		{
			uint8_t a0;	// 1 byte
			// 1 empty byte
			uint16_t a1; // 2 bytes
			uint16_t a2; // 2 bytes
			// 2 empty bytes
			uint32_t a3; // 4 bytes
		};
		// then
		ASSERT_THAT(sizeof(S4), Eq(12));

#pragma pack(push, 1) // Теперь все поля выравниваются по 1 байту
		// when
		struct S4Optimized
		{
			uint8_t a0;
			uint16_t a1;
			uint16_t a2;
			uint32_t a3;
		};
		// then
		ASSERT_THAT(sizeof(S4Optimized), Eq(9));
#pragma pack(pop)

		// when
		class A1 // Размер любого пустого класса/структуры минимум 1 байт
		{
		};
		// then
		ASSERT_THAT(sizeof(A1), Eq(1));

		// when
		class A0 // От количества функций не зависит размер объекта класса
		{
		public:
			void foo0() {}
			void foo1() {}
			void foo2() {}
			void foo3() {}
			void foo4() {}
			void foo5() {}
			void foo6() {}
			void foo7() {}
			void foo8() {}
			void foo9() {}
		};
		// then
		ASSERT_THAT(sizeof(A0), Eq(1));

		// when
		class VirtualA0 // Если класс полиморфный, то размер объекта всегда +8 байт - указатель на таблицу виртуальных функций
		{
		public:
			virtual void foo0() {}
			virtual void foo1() {}
			virtual void foo2() {}
			virtual void foo3() {}
			virtual void foo4() {}
			virtual void foo5() {}
			virtual void foo6() {}
			virtual void foo7() {}
			virtual void foo9() {}
			virtual void foo10() {}
			virtual void foo11() {}
			virtual void foo12() {}
		};
		// then
		ASSERT_THAT(sizeof(VirtualA0), Eq(8)); // 8 - это указатель на таблицу виртуальных функций

		// when 
		class B0 : public A1 // Empty base optimization - когда базовый класс пустой, то его 1 байт не добавляется к общей му размеру наследника, но...
		{
			uint32_t a;
		};
		// then
		ASSERT_THAT(sizeof(B0), Eq(4));

		// when 
		class B1 : public A1 // но... Empty base optimization не работает, когда нестатическим полум класса является объект, чей базовый класс такой же, как наш
			// тогда размер будет 1(base) + 1(a1) + 2(empty for a allign) + 4(a)
		{
			A1 a1;
			uint32_t a;
		};
		// then
		ASSERT_THAT(sizeof(B1), Eq(8));
	}
}