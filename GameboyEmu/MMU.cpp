#include "MMU.h"

namespace Gameboy
{

	MMU::MMU()
	{
		memory[0xFF05] = 0x00;
		memory[0xFF06] = 0x00;
		memory[0xFF07] = 0x00;
		memory[0xFF10] = 0x80;
		memory[0xFF11] = 0xBF;
		memory[0xFF12] = 0xF3;
		memory[0xFF14] = 0xBF;
		memory[0xFF16] = 0x3F;
		memory[0xFF17] = 0x00;
		memory[0xFF19] = 0xBF;
		memory[0xFF1A] = 0x7F;
		memory[0xFF1B] = 0xFF;
		memory[0xFF1C] = 0x9F;
		memory[0xFF1E] = 0xBF;
		memory[0xFF20] = 0xFF;
		memory[0xFF21] = 0x00;
		memory[0xFF22] = 0x00;
		memory[0xFF23] = 0xBF;
		memory[0xFF24] = 0x77;
		memory[0xFF25] = 0xF3;
		memory[0xFF26] = 0xF1;
		memory[0xFF40] = 0x91;
		memory[0xFF42] = 0x00;
		memory[0xFF43] = 0x00;
		memory[0xFF45] = 0x00;
		memory[0xFF47] = 0xFC;
		memory[0xFF48] = 0xFF;
		memory[0xFF49] = 0xFF;
		memory[0xFF4A] = 0x00;
		memory[0xFF4B] = 0x00;
		memory[0xFFFF] = 0x00;
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