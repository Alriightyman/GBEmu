#include "MMU.h"

namespace Gameboy
{

	MMU::MMU()
	{
	}


	MMU::~MMU()
	{
	}

	void MMU::LoadROM(s8* romData, int length)
	{
		for (int i = 0; i < length; ++i)
		{
			memory[i] = romData[i];
		}
	}

	void MMU::Push(Register & sp, u16 value)
	{
		u8 hi = (value >> 8) & 0xFF;
		u8 lo = value & 0xFF;

		sp--;
		Write(sp.Value, hi);
		sp--;
		Write(sp.Value, lo);

	}
	
	u16 MMU::Pop(Register & sp)
	{
		u16 word = Read(sp.Value + 1) << 8;
		word |= Read(sp.Value);

		sp += 2;
		return word;
	}

	u8 MMU::Read(u16 address)
	{
		return memory[address];
	}

	void MMU::Write(u16 address, u8 data)
	{
		if (address < VRAM) // cannot write to ROM 
		{
			// cannot write here
		}
		else if ((address >= ECHORAM) && (address < OAM))
		{
			memory[address] = data;
			Write(address - 0x2000, data);
		}
		else if ((address >= RESERVED) && (address < 0xFEFF))
		{
			// reserved
		}
		else
		{
			memory[address] = data;
		}		
	}

	void MMU::Write(u16 address, u16 value)
	{
		u8 hi = (value >> 8) & 0xFF;
		u8 lo = value & 0xFF;

		Write(address, hi);
		Write(address + 1, lo);
	}
}