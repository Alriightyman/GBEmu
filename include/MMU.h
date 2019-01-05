#pragma once
#include "TypesDef.h"
#include "Register.h"

namespace Gameboy
{

	class MMU
	{
	public:
		enum VectorTable
		{
			VBlankProceedure = 0x40,
			LCDStatProceedure = 0x48,
			TimerProceedure = 0x50,
			SerialProceedure = 0x58,
			JoypadProceedure = 0x60
		};

		enum IORegisters
		{
			DIV = 0xFF04,	// Divider Register (R/W)
			TIMA = 0xFF05,	// Timer counter (R/W)
			TMA = 0xFF06,	// Timer Modulo (R/W)
			TAC = 0xFF07,	// Timer Control (R/W)
			IF = 0xFF0F,
			NR10 = 0xFF10,
			NR11 = 0xFF11,
			NR12 = 0xFF12,
			NR14 = 0xFF14,
			NR21 = 0xFF16,
			NR22 = 0xFF17,
			NR24 = 0xFF19,
			NR30 = 0xFF1A,
			NR31 = 0xFF1B,
			NR32 = 0xFF1C,
			NR33 = 0xFF1E,
			NR41 = 0xFF20,
			NR42 = 0xFF21,
			NR43 = 0xFF22,
			NR44 = 0xFF23,
			NR50 = 0xFF24,
			NR51 = 0xFF25,
			NR52 = 0xFF26,
			LCDC = 0xFF40,	// LCD Control (R/W)
			STAT = 0xFF41,	// LCDC Status (R/W)
			SCY = 0xFF42,	// Scroll Y (R/W)
			SCX = 0xFF43,	// Scroll X (R/W)
			LY = 0xFF44,	// LCDC Y-Coordinate (R)
			LYC = 0xFF45,	// LY Compare (R/W)
			BGP = 0xFF47,	// BG Palette Data (R/W) - Non CGB Mode Only
			OBP0 = 0xFF48,	// Object Palette 0 Data (R/W) - Non CGB Mode Only
			OBP1 = 0xFF49,	// Object Palette 1 Data (R/W) - Non CGB Mode Only
			WY = 0xFF4A,	// Window Y Position (R/W
			WX = 0xFF4B,	// Window X Position minus 7 (R/W)
			IE = 0xFFFF
		};

		enum MemoryMap
		{
			RomBank00 = 0x0000,		//	3FFF	16KB ROM bank 00	From cartridge, fixed bank
			RomBankNN = 0x4000,		//	7FFF	16KB ROM Bank 01~NN	From cartridge, switchable bank via MBC (if any)
			VRAM = 0x8000,			//	9FFF	8KB Video RAM (VRAM)	Only bank 0 in Non-CGB mode; Switchable bank 0/1 in CGB mode
			ExternalRAM = 0xA000,	//	BFFF	8KB External RAM	In cartridge, switchable bank if any
			WRAM00 = 0xC000,		//	CFFF	4KB Work RAM (WRAM) bank 0	
			WRAMNN = 0xD000,		//	DFFF	4KB Work RAM (WRAM) bank 1~N	Only bank 1 in Non-CGB mode; Switchable bank 1~7 in CGB mode
			ECHORAM = 0xE000,		//	FDFF	Mirror of C000~DDFF (ECHO RAM)	Typically not used
			OAM = 0xFE00,			//	FE9F	Sprite attribute table (OAM)	
			RESERVED = 0xFEA0,		//	FEFF	Not Usable	
			IORgisters = 0xFF00,	//	FF7F	I/O Registers	
			HRAM = 0xFF80,			//	FFFE	High RAM (HRAM)	
		};

		enum InterruptBits
		{
			VBlank = 1 << 0,
			LCDStat = 1 << 1,
			Timer = 1 << 2,
			Serial = 1 << 3,
			Joypad = 1 << 4,
		};

	private:
		u8 memory[0xFFFF];

	public:
		MMU();
		~MMU();
		void LoadROM(s8* romData, int length);
		// push value onto stack
		void Push(Register& sp, u16 value);
		// pop value from stack
		u16 Pop(Register& sp);

		u8 Read(u16 address);
		void Write(u16 address, u8 value);
		void Write(u16 address, u16 value);
	};
}
