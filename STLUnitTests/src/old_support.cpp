#include "stdafx.h"

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
