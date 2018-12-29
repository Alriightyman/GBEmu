#pragma once
#include "TypesDef.h"

/// Static Utility class
class Utility
{
public:
	enum Flags
	{
		Z = 1 << 7,
		N = 1 << 6,
		H = 1 << 5,
		C = 1 << 4
	};
public:
	static void SetFlags(u8& flag, u8 mask, bool setFlag);
	static bool IsHalfCarry(u8 x, u8 y);
	static bool IsFullCarry(u8 x, u8 y);
	static bool IsHalfCarry16(u16 x, u16 y);
	static bool IsFullCarry16(u16 x, u16 y);
	static bool IsFlagSet(u8 flag, u8 mask);
	static u8 GetLowByte(u16 word);
	static u8 GetHighByte(u16 word);

private:
	static void SetFlag(u8& flag, u8 mask);
	static void ClearFlag(u8& flag, u8 mask);
};