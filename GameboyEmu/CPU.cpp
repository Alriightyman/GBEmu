#include "CPU.h"
#include "Utility.h"
#include <sstream>
#include <iomanip> 

namespace Gameboy
{
	using CPUFlags = Utility::Flags;

	CPU::CPU(MMU* mmu) : cycleCount(0x00), halt(false), stop(false), pendingEnableInterrupts(false), pendingDisableInterrupts(false), enableInterrupts(false), mmu(mmu)
	{
		af = 0x01B0;
		bc = 0x0013; 
		de = 0x00D8;
		hl = 0x014D;
		sp = 0xFFFE;
		pc = 0x100;
		alu.Initialize(&af);
	}

	CPU::CPU()
	{

	}

	CPU::~CPU()
	{

	}

	std::string CPU::PrintRegisters()
	{
		std::stringstream stringStream;
		char c[8] = { af.Hi, af.Lo, bc.Hi, bc.Lo, de.Hi, de.Lo, hl.Hi, hl.Lo };
		stringStream << "Opcode:  " << lastOpcode << " Registers: "
			<< " AF: " << std::hex << "0x" << static_cast<unsigned short>(af.Value)
			<< " BC: " << std::hex << "0x" << static_cast<unsigned short>(bc.Value)
			<< " DE: " << std::hex << "0x" << static_cast<unsigned short>(de.Value)
			<< " HL: " << std::hex << "0x" << static_cast<unsigned short>(hl.Value)
			<< " SP: " << std::hex << "0x" << static_cast<unsigned short>(sp.Value)
			<< " PC: " << std::hex << "0x" << static_cast<unsigned short>(pc.Value)
			<< " z: " << static_cast<unsigned short>((af.Lo >> 7) & 0x1) << " n: " << static_cast<unsigned short>((af.Lo >> 6) & 0x1) << " h: " << static_cast<unsigned short>((af.Lo >> 5) & 0x1) << " n: " << static_cast<unsigned short>((af.Lo >> 4) & 0x1) << std::endl;
		/*stringStream <<"Opcode: " <<  lastOpcode << " Registers:"
			<< " A: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[0]) & 0xFF)
			<< " F: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[1]) & 0xFF)
			<< " B: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[2]) & 0xFF)
			<< " C: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[3]) & 0xFF)
			<< " D: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[4]) & 0xFF)
			<< " E: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[5]) & 0xFF)
			<< " H: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[6]) & 0xFF)
			<< " L: " <<   std::hex << "0x"<< std::setprecision(4) << (static_cast<unsigned short>(c[7]) & 0xFF)
			<< " SP: " << std::hex << "0x"<<  sp.Value
			<< " PC: " << std::hex << "0x" << pc.Value << std::endl;
			*/
		return stringStream.str();
	}

	void CPU::ResetCycleCount()
	{
		cycleCount = 0;
	}

	bool CPU::IsUpdateFinished()
	{
		return cycleCount > MAXCYCLES;
	}

	u8 CPU::Load8BitImmediateValue()
	{
		return mmu->Read(pc + 1);
	}

	u16 CPU::Load16BitImmediateValue()
	{
		u16 word = mmu->Read(pc + 2) << 8;
		word |= mmu->Read(pc.Value + 1);
		return word;
	}

	void SetLastOpcode(u8 opcode, std::string& lastOpcode)
	{
		char c[2] = { opcode, '/0' };
		std::stringstream stringStream;
		stringStream << std::hex << "0x" << (static_cast<unsigned short>(c[0]) & 0xFF);
		lastOpcode = stringStream.str();
	}

	int CPU::ExecuteOpcode()
	{

		u8 opcode = mmu->Read(pc.Value);
		u8 lastOp = mmu->Read(pc.Value - 1);

		SetLastOpcode(opcode, lastOpcode);
		OpcodeFunction opcodeMethod = Opcodes[opcode];
		(this->*opcodeMethod)();

		if (pendingDisableInterrupts)
		{
			if (lastOp != 0xF3)
			{
				pendingDisableInterrupts = false;
				enableInterrupts = false;
			}
		}

		if (pendingEnableInterrupts)
		{
			if (lastOp != 0xFB)
			{
				pendingEnableInterrupts = false;
				enableInterrupts = true;
			}
		}

		return cycleCount;
	}

	void CPU::UpdateTimers()
	{

	}

	void CPU::CheckInterrupts()
	{
		// only if we have enabledInterrupts
		if (enableInterrupts)
		{
			u8 requestFlag = mmu->Read(MMU::IORegisters::IF);

			if (requestFlag > 0)
			{
				for (int bit = 0; bit < 8; bit++)
				{
					// check for a request
					if (Utility::IsFlagSet(requestFlag, bit))
					{
						u8 interruptEnabledFlag = mmu->Read(MMU::IORegisters::IE);

						if (Utility::IsFlagSet(interruptEnabledFlag, bit))
						{
							RunInterrupts(bit);
						}
					}
				}
			}
		}
	}

	void CPU::RunInterrupts(u8 bit)
	{
		// push pc onto the stack
		mmu->Push(sp, pc.Value);
		cycleCount += 8;

		switch (bit)
		{
		case  MMU::InterruptBits::VBlank:
			pc = MMU::VectorTable::VBlankProceedure;
			break;
		case  MMU::InterruptBits::LCDStat:
			pc = MMU::VectorTable::LCDStatProceedure;
			break;
		case  MMU::InterruptBits::Joypad:
			pc = MMU::VectorTable::JoypadProceedure;
			break;
		case  MMU::InterruptBits::Timer:
			pc = MMU::VectorTable::TimerProceedure;
			break;
		default:
			break;
		}

		enableInterrupts = false;
		u8 ie = mmu->Read(MMU::IE);
		Utility::SetFlags(ie,bit,false);

	}
}
