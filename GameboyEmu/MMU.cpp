#include "MMU.h"

namespace Gameboy
{

	MMU::MMU()
	{
	}


	MMU::~MMU()
	{
	}

	void MMU::Push(Register & sp, u16 value)
	{
		u8 hi = (value >> 8) & 0xFF;
		u8 lo = value & 0xFF;

		Write(sp.Value, hi);
		sp++;
		Write(sp.Value, lo);
		sp++;
	}
	
	u16 MMU::Pop(Register & sp)
	{
		u8 lo = Read(sp.Value);
		u8 hi = Read(sp - 1);

		sp -= 2;

		return (hi << 8) | lo;

	}

	u8 MMU::Read(u16 address)
	{
		return memory[address];
	}

	void MMU::Write(u16 address, u8 value)
	{
		memory[address] = value;
	}

	void MMU::Write(u16 address, u16 value)
	{
		u8 hi = (value >> 8) & 0xFF;
		u8 lo = value & 0xFF;

		Write(address, hi);
		Write(address + 1, lo);
	}
}