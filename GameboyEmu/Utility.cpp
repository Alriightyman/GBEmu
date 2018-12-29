#include "Utility.h"

void Utility::SetFlags(u8& flag, u8 mask, bool setFlag)
{

	if (setFlag)
	{
		SetFlag(flag, mask);
	}
	else
	{
		ClearFlag(flag, mask);
	}
}

bool Utility::IsHalfCarry(u8 a, u8 n)
{
	bool result = false;
	result = ((a & 0x0F) + (n & 0x0F) & 0x10) != 0x0;
	return result;
}

bool Utility::IsFullCarry(u8 x, u8 y)
{
	bool result = false;
	result = ((x & 0x0FF) + (y & 0x0FF) & 0x100) != 0x0;
	return result;
}

bool Utility::IsFullCarry16(u16 x, u16 y)
{
	bool result = false;
	//result = 
	return result;
}

bool Utility::IsFlagSet(u8 flag, u8 mask)
{
	u8 result = flag & mask;

	return result != 0;
}

u8 Utility::GetLowByte(u16 word)
{
	return word & 0x00FF;
}

u8 Utility::GetHighByte(u16 word)
{
	return (word >> 8) & 0x00FF;
}

void Utility::SetFlag(u8& flag, u8 mask)
{
	flag |= mask;
}

void Utility::ClearFlag(u8 & flag, u8 mask)
{
	flag &= ~mask;
}
