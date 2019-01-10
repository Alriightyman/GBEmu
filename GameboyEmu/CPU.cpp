#include "CPU.h"
#include "Utility.h"
#include <sstream>
#include <iomanip> 
#include <map>

namespace Gameboy
{
	using CPUFlags = Utility::Flags;
	std::string opcodeMapping[256] = {
		"NOP",
		"LD BC,",
		"LD (BC),A",
		"INC BC",
		"INC B",
		"DEC B",
		"LD B,",
		"RLCA",
		"LD (16),SP",
		"ADD HL,BC",
		"LDA,(BC)",
		"DEC BC",
		"INC C",
		"DEC C",
		"LD C,8",
		"RRCA",
		"STOP 0",
		" LD DE,16",
		"LD (DE),A",
		"INC DE",
		"INC D",
		"DEC D",
		"LD D,8",
		"RLA",
		"JR 8",
		"ADD HL,DE",
		"LD A,(DE)",
		"DEC DE",
		"INC E",
		"DEC E",
		"LD E,8",
		"RRA",
		"JR NZ,8",
		"LD HL,16",
		"LD (HL+),A",
		"INC HL",
		"INC H",
		"DEC H",
		"LD H,8",
		"DAA",
		"JR Z,8",
		"ADD HL,HL",
		"LD A,(HL+)",
		"DEC HL",
		"INC L",
		"DEC L",
		"LD L,8",
		"CPL",
		"JR NC,8",
		"LD SP,16",
		"LD (HL-),A",
		"INC SP",
		"INC (HL)",
		"DEC (HL)",
		"LD (HL),8",
		"SCF",
		"JR C,8",
		"ADD HL,SP",
		"LD A,(HL-)",
		"DEC SP",
		"INC A",
		"DEC A",
		"LD A,8",
		"CCF",
		"LD B,B",
		"LD B,C",
		"LD B,D",
		"LD B,E",
		"LD B,H",
		"LD B,L",
		"LD B,(HL)",
		"LD B,A",
		"LD C,B",
		"LD C,C",
		"LD C,D",
		"LD C,E",
		"LD C,H",
		"LD C,L",
		"LD C,(HL)",
		"LD C,A",
		"LD D,B",
		"LD D,C",
		"LD D,D",
		"LD D,E",
		"LD D,H",
		"LD D,L",
		"LD D,(HL)",
		"LD D,A",
		"LD E,B",
		"LD E,C",
		"LD E,D",
		"LD E,E",
		"LD E,H",
		"LD E,L",
		"LD E,(HL)",
		"LD E,A",
		"LD H,B",
		"LD H,C",
		"LD H,D",
		"LD H,E",
		"LD H,H",
		"LD H,L",
		"LD H,(HL)",
		"LD H,A",
		"LD L,B",
		"LD L,C",
		"LD L,D",
		"LD L,E",
		"LD L,H",
		"LD L,L",
		"LD L,(HL)",
		"LD L,A",
		"LD (HL),B",
		"LD (HL),C",
		"LD (HL),D",
		"LD (HL),E",
		"LD (HL),H",
		"LD (HL),L",
		"HALT",
		"LD (HL),A",
		"LD A,B",
		"LD A,C",
		"LD A,D",
		"LD A,E",
		"LD A,H",
		"LD A,L",
		"LD A,(HL)",
		"LD A,A",
		"ADD A,B",
		"ADD A,C",
		"ADD A,D",
		"ADD A,E",
		"ADD A,H",
		"ADD A,L",
		"ADD A,(HL)",
		"ADD A,A",
		"ADC A,B",
		"ADC A,C",
		"ADC A,D",
		"ADC A,E",
		"ADC A,H",
		"ADC A,L",
		"ADC A,(HL)",
		"ADC A,A",
		"SUB B",
		"SUB C",
		"SUB D",
		"SUB E",
		"SUB H",
		"SUB L",
		"SUB (HL)",
		"SUB A",
		"SBC A,B",
		"SBC A,C",
		"SBC A,D",
		"SBC A,E",
		"SBC A,H",
		"SBC A,L",
		"SBC A,(HL)",
		"SBC A,A",
		"AND B",
		"AND C",
		"AND D",
		"AND E",
		"AND H",
		"AND L",
		"AND (HL)",
		"AND A",
		"XOR B",
		"XOR C",
		"XOR D",
		"XOR E",
		"XOR H",
		"XOR L",
		"XOR (HL)",
		"XOR A",
		"OR B",
		"OR C",
		"OR D",
		"OR E",
		"OR H",
		"OR L",
		"OR (HL)",
		"OR A",
		"CP B",
		"CP C",
		"CP D",
		"CP E",
		"CP H",
		"CP L",
		"CP (HL)",
		"CP A",
		"RET NZ",
		"POP BC",
		"JP NZ,16",
		"JP 16",
		"CALL NZ,16",
		"PUSH BC",
		"ADD A,8",
		"RST 00H",
		"RET Z",
		"RET",
		"JP Z,16",
		"CB",
		"CALL Z,16",
		"CALL 16",
		"ADC A,8",
		"RST 08H",
		"RET NC",
		"POP DE",
		"JP NC,16",
		"",
		"CALL NC,16",
		"PUSH DE",
		"SUB 8",
		"RST 10H",
		"RET C",
		"RETI",
		"JP C,16",
		"",
		"CALL C,16",
		"",
		"SBC A,8",
		"RST 18H",
		"LDH (8),A",
		"POP HL",
		"LD (C),A",
		"",
		"",
		"PUSH HL",
		"AND 8",
		"RST 20H",
		"ADD SP,8",
		"JP (HL)",
		"LD (16),A",
		"",
		"",
		"",
		"XOR 8",
		"RST 28H",
		"LDH A,(8)",
		"POP AF",
		"LD A,(C)",
		"DI",
		"",
		"PUSH AF",
		"OR 8",
		"RST 30H",
		"LD HL,SP+8",
		"LD SP,HL",
		"LD A,(16)",
		"EI",
		"",
		"",
		"CP 8",
		"RST 38H"
	};
	std::string cbOpcodeMapping[256] = 
	{
		"RLC B",
		"RLC C",
		"RLC D",
		"RLC E",
		"RLC H",
		"RLC L",
		"RLC (HL)",
		"RLC A",
		"RRC B",
		"RRC C",
		"RRC D",
		"RRC E",
		"RRC H",
		"RRC L",
		"RRC (HL)",
		"RRC A",
		"RL B",
		"RL C",
		"RL D",
		"RL E",
		"RL H",
		"RL L",
		"RL (HL)",
		"RL A",
		"RR B",
		"RR C",
		"RR D",
		"RR E",
		"RR H",
		"RR L",
		"RR (HL)",
		"RR A",
		"SLA B",
		"SLA C",
		"SLA D",
		"SLA E",
		"SLA H",
		"SLA L",
		"SLA (HL)",
		"SLA A",
		"SRA B",
		"SRA C",
		"SRA D",
		"SRA E",
		"SRA H",
		"SRA L",
		"SRA (HL)",
		"SRA A",
		"SWAP B",
		"SWAP C",
		"SWAP D",
		"SWAP E",
		"SWAP H",
		"SWAP L",
		"SWAP (HL)",
		"SWAP A",
		"SRL B",
		"SRL C",
		"SRL D",
		"SRL E",
		"SRL H",
		"SRL L",
		"SRL (HL)",
		"SRL A",
		"BIT 0,B",
		"BIT 0,C",
		"BIT 0,D",
		"BIT 0,E",
		"BIT 0,H",
		"BIT 0,L",
		"BIT 0,(HL)",
		"BIT 0,A",
		"BIT 1,B",
		"BIT 1,C",
		"BIT 1,D",
		"BIT 1,E",
		"BIT 1,H",
		"BIT 1,L",
		"BIT 1,(HL)",
		"BIT 1,A",
		"BIT 2,B",
		"BIT 2,C",
		"BIT 2,D",
		"BIT 2,E",
		"BIT 2,H",
		"BIT 2,L",
		"BIT 2,(HL)",
		"BIT 2,A",
		"BIT 3,B",
		"BIT 3,C",
		"BIT 3,D",
		"BIT 3,E",
		"BIT 3,H",
		"BIT 3,L",
		"BIT 3,(HL)",
		"BIT 3,A",
		"BIT 4,B",
		"BIT 4,C",
		"BIT 4,D",
		"BIT 4,E",
		"BIT 4,H",
		"BIT 4,L",
		"BIT 4,(HL)",
		"BIT 4,A",
		"BIT 5,B",
		"BIT 5,C",
		"BIT 5,D",
		"BIT 5,E",
		"BIT 5,H",
		"BIT 5,L",
		"BIT 5,(HL)",
		"BIT 5,A",
		"BIT 6,B",
		"BIT 6,C",
		"BIT 6,D",
		"BIT 6,E",
		"BIT 6,H",
		"BIT 6,L",
		"BIT 6,(HL)",
		"BIT 6,A",
		"BIT 7,B",
		"BIT 7,C",
		"BIT 7,D",
		"BIT 7,E",
		"BIT 7,H",
		"BIT 7,L",
		"BIT 7,(HL)",
		"BIT 7,A",
		"RES 0,B",
		"RES 0,C",
		"RES 0,D",
		"RES 0,E",
		"RES 0,H",
		"RES 0,L",
		"RES 0,(HL)",
		"RES 0,A",
		"RES 1,B",
		"RES 1,C",
		"RES 1,D",
		"RES 1,E",
		"RES 1,H",
		"RES 1,L",
		"RES 1,(HL)",
		"RES 1,A",
		"RES 2,B",
		"RES 2,C",
		"RES 2,D",
		"RES 2,E",
		"RES 2,H",
		"RES 2,L",
		"RES 2,(HL)",
		"RES 2,A",
		"RES 3,B",
		"RES 3,C",
		"RES 3,D",
		"RES 3,E",
		"RES 3,H",
		"RES 3,L",
		"RES 3,(HL)",
		"RES 3,A",
		"RES 4,B",
		"RES 4,C",
		"RES 4,D",
		"RES 4,E",
		"RES 4,H",
		"RES 4,L",
		"RES 4,(HL)",
		"RES 4,A",
		"RES 5,B",
		"RES 5,C",
		"RES 5,D",
		"RES 5,E",
		"RES 5,H",
		"RES 5,L",
		"RES 5,(HL)",
		"RES 5,A",
		"RES 6,B",
		"RES 6,C",
		"RES 6,D",
		"RES 6,E",
		"RES 6,H",
		"RES 6,L",
		"RES 6,(HL)",
		"RES 6,A",
		"RES 7,B",
		"RES 7,C",
		"RES 7,D",
		"RES 7,E",
		"RES 7,H",
		"RES 7,L",
		"RES 7,(HL)",
		"RES 7,A",
		"SET 0,B",
		"SET 0,C",
		"SET 0,D",
		"SET 0,E",
		"SET 0,H",
		"SET 0,L",
		"SET 0,(HL)",
		"SET 0,A",
		"SET 1,B",
		"SET 1,C",
		"SET 1,D",
		"SET 1,E",
		"SET 1,H",
		"SET 1,L",
		"SET 1,(HL)",
		"SET 1,A",
		"SET 2,B",
		"SET 2,C",
		"SET 2,D",
		"SET 2,E",
		"SET 2,H",
		"SET 2,L",
		"SET 2,(HL)",
		"SET 2,A",
		"SET 3,B",
		"SET 3,C",
		"SET 3,D",
		"SET 3,E",
		"SET 3,H",
		"SET 3,L",
		"SET 3,(HL)",
		"SET 3,A",
		"SET 4,B",
		"SET 4,C",
		"SET 4,D",
		"SET 4,E",
		"SET 4,H",
		"SET 4,L",
		"SET 4,(HL)",
		"SET 4,A",
		"SET 5,B",
		"SET 5,C",
		"SET 5,D",
		"SET 5,E",
		"SET 5,H",
		"SET 5,L",
		"SET 5,(HL)",
		"SET 5,A",
		"SET 6,B",
		"SET 6,C",
		"SET 6,D",
		"SET 6,E",
		"SET 6,H",
		"SET 6,L",
		"SET 6,(HL)",
		"SET 6,A",
		"SET 7,B",
		"SET 7,C",
		"SET 7,D",
		"SET 7,E",
		"SET 7,H",
		"SET 7,L",
		"SET 7,(HL)",
		"SET 7,A"
	};

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
		stringStream 
			<< "\nAF: " << std::hex << "0x" << static_cast<unsigned short>(af.Value)
			<< "\nBC: " << std::hex << "0x" << static_cast<unsigned short>(bc.Value)
			<< "\nDE: " << std::hex << "0x" << static_cast<unsigned short>(de.Value)
			<< "\nHL: " << std::hex << "0x" << static_cast<unsigned short>(hl.Value)
			<< "\nSP: " << std::hex << "0x" << static_cast<unsigned short>(sp.Value)
			<< "\nPC: " << std::hex << "0x" << static_cast<unsigned short>(pc.Value)
			<< "\nz: " << static_cast<unsigned short>((af.Lo >> 7) & 0x1) << " n: " << static_cast<unsigned short>((af.Lo >> 6) & 0x1) << " h: " << static_cast<unsigned short>((af.Lo >> 5) & 0x1) << " n: " << static_cast<unsigned short>((af.Lo >> 4) & 0x1) << std::endl;
		return stringStream.str();
	}

	std::string CPU::PrintOpcode()
	{
		std::string opcode = opcodeMapping[lastOpcode];

		if (opcode == "CB")
		{
			opcode = cbOpcodeMapping[Load8BitImmediateValue()];
		}
		else
		{
			auto pos = opcode.find("8");
			if (pos != std::string::npos)
			{
				opcode.replace(pos, 1, (char*)Load8BitImmediateValue());
			}

			pos = opcode.find("16");
			if (pos != std::string::npos)
			{
				opcode.replace(pos, 2, (char*)Load16BitImmediateValue());
			}
		}
		return "0x" + static_cast<unsigned short>(lastOpcode) + '\t' + opcode;
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

	int CPU::ExecuteOpcode()
	{

		u8 opcode = mmu->Read(pc.Value);
		lastOpcode = mmu->Read(pc.Value - 1);

		OpcodeFunction opcodeMethod = Opcodes[opcode];
		(this->*opcodeMethod)();

		if (pendingDisableInterrupts)
		{
			if (lastOpcode != 0xF3)
			{
				pendingDisableInterrupts = false;
				enableInterrupts = false;
			}
		}

		if (pendingEnableInterrupts)
		{
			if (lastOpcode != 0xFB)
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
