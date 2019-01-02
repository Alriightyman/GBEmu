#include "CPU.h"
#include "Utility.h"
#include <sstream>

namespace Gameboy
{
	using CPUFlags = Utility::Flags;

	CPU::CPU() : cycleCount(0x00), halt(false), stop(false), disableInterrupts(false), enableInterrupts(false)
	{
		af = 0x01B0;
		bc = 0x0013; 
		de = 0x00D8;
		hl = 0x014D;
		sp = 0xFFFE;
	}

	CPU::~CPU()
	{
	}

	std::string CPU::PrintRegisters()
	{
		std::stringstream stringStream;

		stringStream << "Registers: " << "A: " << af.Hi
			<< "F: " << std::hex << af.Lo
			<< "B: " << std::hex << bc.Hi
			<< "C: " << std::hex << bc.Lo
			<< "D: " << std::hex << de.Hi
			<< "E: " << std::hex << de.Lo
			<< "H: " << std::hex << hl.Hi
			<< "L: " << std::hex << hl.Lo
			<< "SP: " << std::hex << sp.Value
			<< "PC: " << std::hex << pc.Value << std::endl;

		return stringStream.str();
	}

	bool CPU::IsUpdateFinished()
	{
		return cycleCount > MAXCYCLES;
	}

	u8 CPU::Load8BitImmediateValue()
	{
		return mmu.Read(pc + 1);
	}

	u16 CPU::Load16BitImmediateValue()
	{
		u8 lo = mmu.Read(pc + 1);
		u8 hi = mmu.Read(pc + 2);

		return (hi << 8) | lo;
	}

	int CPU::ExecuteOpcode()
	{
		u8 opcode = mmu.Read(pc.Value);
		OpcodeFunction opcodeMethod = Opcodes[opcode];
		(this->*opcodeMethod)();

		return cycleCount;
	}

	void CPU::UpdateTimers()
	{
	}

	void CPU::RunInterrupts()
	{
	}

#pragma region 8-Bit Loads

#pragma region 1. LD nn, n
	/// <summary>
	/// 1. LD nn,n
	///		Description:
	///			Put value nn into n.
	///				Use with :
	///			nn = B, C, D, E, H, L, BC, DE, HL, SP
	///				n = 8 bit immediate value
	/// </summary>
	/// <param name="reg">The reg.</param>
	/// <param name="immediateValue">The immediate value.</param>
	void CPU::LD(u8 & reg, u8 value)
	{
		reg = value;
	}

	// LD B, n
	void CPU::Opcode06()
	{		
		LD(bc.Hi, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

	// LD C, n
	void CPU::Opcode0E()
	{
		LD(bc.Lo, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

	// LD D, n
	void CPU::Opcode16()
	{
		LD(de.Hi, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

	// LD E, n
	void CPU::Opcode1E()
	{
		LD(de.Lo, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
	// LD H, n
	void CPU::Opcode26()
	{
		LD(hl.Hi, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
	// LD L, n
	void CPU::Opcode2E()
	{
		LD(hl.Lo, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 2. LD r1,r2
	///	2. LD r1, r2
	///		Description :
	///	Put value r2 into r1.
	///		Use with :
	///	r1, r2 = A, B, C, D, E, H, L, (HL)
	// LD A,A
	void CPU::Opcode7F()
	{
		LD(af.Hi, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD A,B
	void CPU::Opcode78()
	{
		LD(af.Hi, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD A,C
	void CPU::Opcode79()
	{
		LD(af.Hi, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD A,D
	void CPU::Opcode7A()
	{
		LD(af.Hi, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD A,E
	void CPU::Opcode7B()
	{
		LD(af.Hi, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD A,H
	void CPU::Opcode7C()
	{
		LD(af.Hi, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD A,L
	void CPU::Opcode7D()
	{
		LD(af.Hi, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD A, (HL)
	void CPU::Opcode7E()
	{
		LD(af.Hi, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	// LD B, B
	void CPU::Opcode40()
	{
		LD(bc.Hi, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD B, C
	void CPU::Opcode41()
	{
		LD(bc.Hi, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD B, D
	void CPU::Opcode42()
	{
		LD(bc.Hi, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD B, E
	void CPU::Opcode43()
	{
		LD(bc.Hi, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD B, H
	void CPU::Opcode44()
	{
		LD(bc.Hi, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD B, L
	void CPU::Opcode45()
	{
		LD(bc.Hi, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD B, (HL)
	void CPU::Opcode46()
	{
		LD(bc.Hi, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD C, B
	void CPU::Opcode48()
	{
		LD(bc.Lo, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD C, C
	void CPU::Opcode49()
	{
		LD(bc.Lo, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD C, D
	void CPU::Opcode4A()
	{
		LD(bc.Lo, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD C, E
	void CPU::Opcode4B()
	{
		LD(bc.Lo, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD C, H
	void CPU::Opcode4C()
	{
		LD(bc.Lo, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD C, L
	void CPU::Opcode4D()
	{
		LD(bc.Lo, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD C, (HL)
	void CPU::Opcode4E()
	{
		LD(bc.Lo, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD D, B
	void CPU::Opcode50()
	{
		LD(de.Hi, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD D, C
	void CPU::Opcode51()
	{
		LD(de.Hi, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD D, D
	void CPU::Opcode52()
	{
		LD(de.Hi, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD D, E
	void CPU::Opcode53()
	{
		LD(de.Hi, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD D, H
	void CPU::Opcode54()
	{
		LD(de.Hi, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD D, L
	void CPU::Opcode55()
	{
		LD(de.Hi, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD D, (HL)
	void CPU::Opcode56()
	{
		LD(de.Hi, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD E, B
	void CPU::Opcode58()
	{
		LD(de.Lo, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD E, C
	void CPU::Opcode59()
	{
		LD(de.Lo, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD E, D
	void CPU::Opcode5A()
	{
		LD(de.Lo, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD E, E
	void CPU::Opcode5B()
	{
		LD(de.Lo, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD E, H
	void CPU::Opcode5C()
	{
		LD(de.Lo, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD E, L
	void CPU::Opcode5D()
	{
		LD(de.Lo, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD E, (HL)
	void CPU::Opcode5E()
	{
		LD(de.Lo, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD H, B
	void CPU::Opcode60()
	{
		LD(hl.Hi, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD H, C
	void CPU::Opcode61()
	{
		LD(hl.Hi, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD H, D
	void CPU::Opcode62()
	{
		LD(hl.Hi, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD H, E
	void CPU::Opcode63()
	{
		LD(hl.Hi, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD H, H
	void CPU::Opcode64()
	{
		LD(hl.Hi, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD H, L
	void CPU::Opcode65()
	{
		LD(hl.Hi, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD H, (HL)
	void CPU::Opcode66()
	{
		LD(hl.Hi, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD L, B
	void CPU::Opcode68()
	{
		LD(hl.Lo, bc.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD L, C
	void CPU::Opcode69()
	{
		LD(hl.Lo, bc.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD L, D
	void CPU::Opcode6A()
	{
		LD(hl.Lo, de.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD L, E
	void CPU::Opcode6B()
	{
		LD(hl.Lo, de.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD L, H
	void CPU::Opcode6C()
	{
		LD(hl.Lo, hl.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD L, L
	void CPU::Opcode6D()
	{
		LD(hl.Lo, hl.Lo);
		pc++;
		cycleCount += 4;
	}
	// LD L, (HL)
	void CPU::Opcode6E()
	{
		LD(hl.Lo, mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	// LD (HL), B
	void CPU::Opcode70()
	{
		mmu.Write(hl.Value, bc.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), C
	void CPU::Opcode71()
	{
		mmu.Write(hl.Value, bc.Lo);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), D
	void CPU::Opcode72()
	{
		mmu.Write(hl.Value, de.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), E
	void CPU::Opcode73()
	{
		mmu.Write(hl.Value, de.Lo);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), H
	void CPU::Opcode74()
	{
		mmu.Write(hl.Value, hl.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), L
	void CPU::Opcode75()
	{
		mmu.Write(hl.Value, hl.Lo);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), n
	void CPU::Opcode36()
	{
		mmu.Write(hl.Value, Load8BitImmediateValue());
		pc+=2;
		cycleCount += 12;
	}

	//
#pragma endregion

#pragma region 3. LD A, n
	// 3. LD A,n
	// Description :
	//		Put value n into A.
	//		Use with :
	//			n = A, B, C, D, E, H, L, (BC), (DE), (HL), (nn), #
	//			nn = two byte immediate value. (LS byte first.)
	// LD A, (BC)
	void CPU::Opcode0A()
	{
		LD(af.Hi, mmu.Read(bc.Value));
		pc++;
		cycleCount += 8;
	}
	// LD A, (DE)
	void CPU::Opcode1A()
	{
		LD(af.Hi, mmu.Read(de.Value));
		pc++;
		cycleCount += 8;
	}
	// LD A, (nn)
	void CPU::OpcodeFA()
	{
		LD(af.Hi, mmu.Read(Load16BitImmediateValue()));
		pc += 3;
		cycleCount += 16;
	}
	// LD A, #
	void CPU::Opcode3E()
	{
		LD(af.Hi, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 4. LD n, A
	// LD B, A
	void CPU::Opcode47()
	{
		LD(bc.Hi, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD C, A
	void CPU::Opcode4F()
	{
		LD(bc.Lo, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD D, A
	void CPU::Opcode57()
	{
		LD(de.Hi, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD E, A
	void CPU::Opcode5F()
	{
		LD(de.Lo, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD H, A
	void CPU::Opcode67()
	{
		LD(hl.Hi, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD L, A
	void CPU::Opcode6F()
	{
		LD(hl.Lo, af.Hi);
		pc++;
		cycleCount += 4;
	}
	// LD (BC), A
	void CPU::Opcode02()
	{
		mmu.Write(bc.Value, af.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (DE), A
	void CPU::Opcode12()
	{
		mmu.Write(de.Value, af.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (HL), A
	void CPU::Opcode77()
	{
		mmu.Write(hl.Value, af.Hi);
		pc++;
		cycleCount += 8;
	}
	// LD (nn), A
	void CPU::OpcodeEA()
	{
		mmu.Write(Load16BitImmediateValue(), af.Hi);
		pc += 3;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 5. LD A,(C)
	// 5. LD A,(C)
	// Description:
	// 	   Put value at address $FF00 + register C into A.
	//	   Same as : LD A, ($FF00 + C)
	void CPU::OpcodeF2()
	{
		LD(af.Hi, mmu.Read(0xFF00 + bc.Lo));
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 6. LD (C),A
	// 6. LD (C),A
	// Description :
	//		Put A into address $FF00 + register C.
	void CPU::OpcodeE2()
	{
		mmu.Write((0xFF0 + bc.Lo), af.Hi);
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 7. LD A,(HLD); 8. LD A, (HL - ); 9. LDD A, (HL)
	// Description:
	// Put value at address HL into A. Decrement HL.
	//	Same as : LD A, (HL)-DEC HL
	void CPU::Opcode3A()
	{
		LD(af.Hi, mmu.Read(hl.Value));
		hl--;
		pc++;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 10. LD (HLD),A; 11. LD (HL-), A; 12. LDD (HL), A
	// Description:
	// Put A into memory address HL.Decrement HL.
	//	Same as : LD (HL), A - DEC HL
	void CPU::Opcode32()
	{
		mmu.Write(hl.Value, af.Hi);
		hl--;
		pc++;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 13. LD A,(HLI); 14. LD A, (HL+); 15. LDI A, (HL)
	// Description:
	// Put value at address HL into A.Increment HL.
	//		Same as : LD A, (HL)-INC HL
	void CPU::Opcode2A()
	{
		LD(af.Hi, mmu.Read(hl.Value));
		hl++;
		pc++;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 16. LD (HLI),A; 17. LD (HL+), A; 18. LDI (HL), A
		// Description :
		//	  Put A into memory address HL.Increment HL.
		//	  Same as : LD (HL), A - INC HL
	void CPU::Opcode22()
	{
		mmu.Write(hl.Value, af.Hi);
		hl++;
		pc++;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 19. LDH (n),A
	// Description :
	//		Put A into memory address $FF00 + n.
	//		Use with :
	//	 		n = one byte immediate value.
	void CPU::OpcodeE0()
	{
		mmu.Write((0xff00 + Load8BitImmediateValue()), af.Hi);
		pc += 2;
		cycleCount += 12;
	}
#pragma endregion

#pragma region 20. LDH A,(n)
	// Description:
	//	   Put memory address $FF00 + n into A.
	//	   Use with :
	//		   n = one byte immediate value.
	void CPU::OpcodeF0()
	{
		LD(af.Hi, mmu.Read(0xFF00 + Load8BitImmediateValue()));
		pc += 2;
		cycleCount += 12;
	}
#pragma endregion


#pragma endregion

#pragma region 16-Bit Loads	
	/// <summary>
	/// Put 16-bit register value or immediate value into a 16-bit register
	/// </summary>
	/// <param name="reg"> BC,DE,HL or SP</param>
	/// <param name="value"> .</param>
	void CPU::LD(u16& reg, u16 value)
	{
		reg = value;
	}

#pragma region 1. LD n,nn
	// Description :
	//	Put value nn into n.
	//	Use with :
	//		n = BC, DE, HL, SP
	//		nn = 16 bit immediate value	

	/// <summary>
	/// Put immediate value into Register BC
	/// </summary>
	void CPU::Opcode01()
	{
		LD(bc.Value, Load16BitImmediateValue());
		pc += 3;
		cycleCount += 12;
	}
	/// <summary>
	/// Put immediate value into Register DE
	/// </summary>
	void CPU::Opcode11()
	{
		LD(de.Value, Load16BitImmediateValue());
		pc += 3;
		cycleCount += 12;
	}
	/// <summary>
	/// Put immediate value into Register HL
	/// </summary>
	void CPU::Opcode21()
	{
		LD(hl.Value, Load16BitImmediateValue());
		pc += 3;
		cycleCount += 12;
	}
	/// <summary>
	/// Put immediate value into Stack Pointer
	/// </summary>
	void CPU::Opcode31()
	{
		LD(sp.Value, Load16BitImmediateValue());
		pc += 3;
		cycleCount += 12;
	}
#pragma endregion

#pragma region 2. LD SP,HL			
	/// <summary>
	/// Put HL into Stack Pointer(SP).
	/// </summary>
	void CPU::OpcodeF9()
	{
		LD(sp.Value, hl.Value);
		pc++;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 3. LD HL,SP+n; 4. LDHL SP, n	
	/// <summary>
	/// Description:
	/// Put SP + n effective address into HL.
	///	Use with :
	///		n = one byte signed immediate value.
	///	Flags affected :
	///		Z - Reset.
	///		N - Reset.
	///		H - Set or reset according to operation.
	///		C - Set or reset according to operation.
	/// </summary>
	void CPU::OpcodeF8()
	{
		u8 immediateValue = Load8BitImmediateValue();
		LD(hl.Value, sp.Value + immediateValue);

		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, Utility::IsHalfCarry16(sp.Value, immediateValue));
		Utility::SetFlags(af.Lo, CPUFlags::C, Utility::IsFullCarry16(sp.Value, immediateValue));
		pc += 2;
		cycleCount += 12;
	}

#pragma endregion

#pragma region 5. LD (nn),SP	
	/// <summary>
	/// Description:
	///		Put Stack Pointer(SP) at address n.
	///		Use with :
	///			nn = two byte immediate address.
	/// </summary>
	void CPU::Opcode08()
	{
		mmu.Write(Load16BitImmediateValue(), sp.Value);
		pc += 3;
		cycleCount += 20;

	}
#pragma endregion

#pragma region 6. PUSH nn

	void CPU::Push(u16 value)
	{
		u8 hiByte = Utility::GetHighByte(value);
		u8 loByte = Utility::GetLowByte(value);

		mmu.Write(sp - 1, hiByte);
		mmu.Write(sp - 2, loByte);

		sp -= 2;
		
	}

	///<summary>
	/// Description :
	///			Push register pair nn onto stack.
	///				Decrement Stack Pointer(SP) twice.
	///				Use with :
	///			nn = AF, BC, DE, HL
	///</ summary>
	
	// push AF
	void CPU::OpcodeF5()
	{
		Push(af.Value);
		cycleCount += 16;
	}

	// push BC
	void CPU::OpcodeC5()
	{
		Push(bc.Value);
		cycleCount += 16;
	}

	//push DE
	void CPU::OpcodeD5()
	{
		Push(de.Value);
		cycleCount += 16;
	}
	// push HL
	void CPU::OpcodeE5()
	{
		Push(hl.Value);
		cycleCount += 16;
	}
#pragma endregion

#pragma region 7. POP nn
	
	/// <summary>
	/// Description:
	///		Pop two bytes off stack into register pair nn.
	///		Increment Stack Pointer(SP) twice.
	///	Use with :
	///		nn = AF, BC, DE, HL
	/// </summary>
	/// <returns> a word value from the stack</returns>
	u16 CPU::Pop()
	{
		u8 loByte = mmu.Read(sp.Value);
		u8 hiByte = mmu.Read(sp.Value + 1);
		pc += 2;

		return (hiByte << 8) | loByte;
	}

	// pop AF
	void CPU::OpcodeF1()
	{
		af = Pop();
		cycleCount += 12;
	}

	// pop BC
	void CPU::OpcodeC1()
	{
		bc = Pop();
		cycleCount += 12;
	}

	// pop DE
	void CPU::OpcodeD1()
	{
		de = Pop();
		cycleCount += 12;
	}

	// pop HL
	void CPU::OpcodeE1()
	{
		hl = Pop();
		cycleCount += 12;
	}
#pragma endregion

#pragma endregion

#pragma region 8-Bit ALU
#pragma region  ADD A,n
	
	/// <summary>
	/// Add A to A
	/// </summary>
	void CPU::Opcode87()
	{
		alu.Add(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add B to A
	/// </summary>
	void CPU::Opcode80()
	{
		alu.Add(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add C to A
	/// </summary>
	void CPU::Opcode81()
	{
		alu.Add(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add D to A
	/// </summary>
	void CPU::Opcode82()
	{
		alu.Add(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add E to A
	/// </summary>
	void CPU::Opcode83()
	{
		alu.Add(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add H to A
	/// </summary>
	void CPU::Opcode84()
	{
		alu.Add(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add L to A
	/// </summary>
	void CPU::Opcode85()
	{
		alu.Add(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// Add (HL) to A
	/// </summary>
	void CPU::Opcode86()
	{
		alu.Add(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// <summary>
	/// Add A to A
	/// </summary>
	void CPU::OpcodeC6()
	{
		alu.Add(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

#pragma endregion

#pragma region 2. ADC A,n
	
	/// <summary>
	/// ADC A, A
	/// </summary>
	void CPU::Opcode8F()
	{
		alu.Adc(af.Hi);
		pc++;
		cycleCount += 4;
	}
	
	/// ADC A, B
	/// </summary>
	void CPU::Opcode88()
	{
		alu.Adc(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, C
	/// </summary>
	void CPU::Opcode89()
	{
		alu.Adc(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, D
	/// </summary>
	void CPU::Opcode8A()
	{
		alu.Adc(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, E
	/// </summary>
	void CPU::Opcode8B()
	{
		alu.Adc(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, H
	/// </summary>
	void CPU::Opcode8C()
	{
		alu.Adc(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, L
	/// </summary>
	void CPU::Opcode8D()
	{
		alu.Adc(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// ADC A, (HL)
	/// </summary>
	void CPU::Opcode8E()
	{
		alu.Adc(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// <summary>
	/// ADC A, d8
	/// </summary>
	void CPU::OpcodeCE()
	{
		alu.Adc(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

#pragma endregion 

#pragma region 3. SUB n
	
	/// <summary>
	/// SUB A
	/// </summary>
	void CPU::Opcode97()
	{
		alu.Sub(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB B
	/// </summary>
	void CPU::Opcode90()
	{
		alu.Sub(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB C
	/// </summary>
	void CPU::Opcode91()
	{
		alu.Sub(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB D
	/// </summary>
	void CPU::Opcode92()
	{
		alu.Sub(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB E
	/// </summary>
	void CPU::Opcode93()
	{
		alu.Sub(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB H
	/// </summary>
	void CPU::Opcode94()
	{
		alu.Sub(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB L
	/// </summary>
	void CPU::Opcode95()
	{
		alu.Sub(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SUB (HL)
	/// </summary>
	void CPU::Opcode96()
	{
		alu.Sub(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// <summary>
	/// SUB d8
	/// </summary>
	void CPU::OpcodeD6()
	{
		alu.Sub(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion

#pragma region 4. SBC A,n	
	/// <summary>
	/// SBC A, A
	/// </summary>
	void CPU::Opcode9F()
	{
		alu.Sbc(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, B
	/// </summary>
	void CPU::Opcode98()
	{
		alu.Sbc(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, C
	/// </summary>
	void CPU::Opcode99()
	{
		alu.Sbc(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, D
	/// </summary>
	void CPU::Opcode9A()
	{
		alu.Sbc(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, E
	/// </summary>
	void CPU::Opcode9B()
	{
		alu.Sbc(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, H
	/// </summary>
	void CPU::Opcode9C()
	{
		alu.Sbc(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, L
	/// </summary>
	void CPU::Opcode9D()
	{
		alu.Sbc(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// SBC A, (HL)
	/// </summary>
	void CPU::Opcode9E()
	{
		alu.Sbc(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// <summary>
	/// SBC A, d8
	/// </summary>
	void CPU::OpcodeDE()
	{
		alu.Sbc(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}

#pragma endregion

#pragma region 5. AND n

	/// <summary>
	/// AND A
	/// </summary>
	void CPU::OpcodeA7()
	{
		alu.And(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND B
	/// </summary>
	void CPU::OpcodeA0()
	{
		alu.And(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND C
	/// </summary>
	void CPU::OpcodeA1()
	{
		alu.And(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND D
	/// </summary>
	void CPU::OpcodeA2()
	{
		alu.And(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND E
	/// </summary>
	void CPU::OpcodeA3()
	{
		alu.And(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND H
	/// </summary>
	void CPU::OpcodeA4()
	{
		alu.And(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND L
	/// </summary>
	void CPU::OpcodeA5()
	{
		alu.And(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// <summary>
	/// AND (HL)
	/// </summary>
	void CPU::OpcodeA6()
	{
		alu.And(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// <summary>
	/// AND d8
	/// </summary>
	void CPU::OpcodeE6()
	{
		alu.And(Load8BitImmediateValue());
		pc+=2;
		cycleCount += 8;
	}

#pragma endregion

#pragma region 6. OR n

	/// OR A
	void CPU::OpcodeB7()
	{
		alu.OR(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// OR B
	void CPU::OpcodeB0()
	{
		alu.OR(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// OR C
	void CPU::OpcodeB1()
	{
		alu.OR(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// OR D
	void CPU::OpcodeB2()
	{
		alu.OR(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// OR E
	void CPU::OpcodeB3()
	{
		alu.OR(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// OR H
	void CPU::OpcodeB4()
	{
		alu.OR(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// OR L
	void CPU::OpcodeB5()
	{
		alu.OR(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// OR (HL)
	void CPU::OpcodeB6()
	{
		alu.OR(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// OR d8
	void CPU::OpcodeF6()
	{
		alu.OR(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}


#pragma endregion

#pragma region 7. XOR n

	/// XOR A
	void CPU::OpcodeAF()
	{
		alu.XOR(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// XOR B
	void CPU::OpcodeA8()
	{
		alu.XOR(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// XOR C
	void CPU::OpcodeA9()
	{
		alu.XOR(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// XOR D
	void CPU::OpcodeAA()
	{
		alu.XOR(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// XOR E
	void CPU::OpcodeAB()
	{
		alu.XOR(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// XOR H
	void CPU::OpcodeAC()
	{
		alu.XOR(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// XOR L
	void CPU::OpcodeAD()
	{
		alu.XOR(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// XOR (HL)
	void CPU::OpcodeAE()
	{
		alu.XOR(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}

	/// XOR d8
	void CPU::OpcodeEE()
	{
		alu.XOR(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion 

#pragma region 8. CP n

	/// CP A
	void CPU::OpcodeBF()
	{
		alu.CP(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// CP B
	void CPU::OpcodeB8()
	{
		alu.CP(bc.Hi);
		pc++;
		cycleCount += 4;
	}
	/// CP C
	void CPU::OpcodeB9()
	{
		alu.CP(bc.Lo);
		pc++;
		cycleCount += 4;
	}
	/// CP D
	void CPU::OpcodeBA()
	{
		alu.CP(de.Hi);
		pc++;
		cycleCount += 4;
	}
	/// CP E
	void CPU::OpcodeBB()
	{
		alu.CP(de.Lo);
		pc++;
		cycleCount += 4;
	}
	/// CP H
	void CPU::OpcodeBC()
	{
		alu.CP(hl.Hi);
		pc++;
		cycleCount += 4;
	}
	/// CP L
	void CPU::OpcodeBD()
	{
		alu.CP(hl.Lo);
		pc++;
		cycleCount += 4;
	}
	/// CP (HL)
	void CPU::OpcodeBE()
	{
		alu.CP(mmu.Read(hl.Value));
		pc++;
		cycleCount += 8;
	}
	/// CP d8
	void CPU::OpcodeFE()
	{
		alu.CP(Load8BitImmediateValue());
		pc += 2;
		cycleCount += 8;
	}
#pragma endregion 

#pragma region 9. INC n

	/// INC A
	void CPU::Opcode3C()
	{
		alu.Inc(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// INC B
	void CPU::Opcode04()
	{
		alu.Inc(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// INC C
	void CPU::Opcode0C()
	{
		alu.Inc(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// INC D
	void CPU::Opcode14()
	{
		alu.Inc(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// INC E
	void CPU::Opcode1C()
	{
		alu.Inc(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// INC H
	void CPU::Opcode24()
	{
		alu.Inc(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// INC L
	void CPU::Opcode2C()
	{
		alu.Inc(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// INC (HL)
	void CPU::Opcode34()
	{
		u8 value = mmu.Read(hl.Value);
		alu.Inc(value);
		mmu.Write(hl.Value, value);
		pc++;
		cycleCount += 12;
	}


#pragma endregion 

#pragma region 10. DEC n

	/// DEC A
	void CPU::Opcode3D()
	{
		alu.Dec(af.Hi);
		pc++;
		cycleCount += 4;
	}

	/// DEC B
	void CPU::Opcode05()
	{
		alu.Dec(bc.Hi);
		pc++;
		cycleCount += 4;
	}

	/// DEC C
	void CPU::Opcode0D()
	{
		alu.Dec(bc.Lo);
		pc++;
		cycleCount += 4;
	}

	/// DEC D
	void CPU::Opcode15()
	{
		alu.Dec(de.Hi);
		pc++;
		cycleCount += 4;
	}

	/// DEC E
	void CPU::Opcode1D()
	{
		alu.Dec(de.Lo);
		pc++;
		cycleCount += 4;
	}

	/// DEC H
	void CPU::Opcode25()
	{
		alu.Dec(hl.Hi);
		pc++;
		cycleCount += 4;
	}

	/// DEC L
	void CPU::Opcode2D()
	{
		alu.Dec(hl.Lo);
		pc++;
		cycleCount += 4;
	}

	/// DEC (HL)
	void CPU::Opcode35()
	{
		u8 value = mmu.Read(hl.Value);
		alu.Dec(value);
		mmu.Write(hl.Value, value);
		pc++;
		cycleCount += 12;
	}
#pragma endregion 

#pragma endregion 

#pragma region 16-Bit Arithmetic

#pragma region 1. ADD HL,n

	/// ADD HL, BC
	void CPU::Opcode09()
	{
		alu.Add(hl.Value, bc.Value);
		pc++;
		cycleCount += 8;
	}
	/// ADD HL, DE
	void CPU::Opcode19()
	{
		alu.Add(hl.Value, de.Value);
		pc++;
		cycleCount += 8;
	}
	/// ADD HL, HL
	void CPU::Opcode29()
	{
		alu.Add(hl.Value, hl.Value);
		pc++;
		cycleCount += 8;
	}
	/// ADD HL, sp
	void CPU::Opcode39()
	{
		alu.Add(hl.Value, sp.Value);
		pc++;
		cycleCount += 8;
	}

#pragma endregion

#pragma region 2. ADD SP,n
	
	void CPU::OpcodeE8()
	{
		alu.AddSP(sp.Value, Load8BitImmediateValue());
		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 3. INC nn
	/// <summary>
	/// Increment register nn. 
	/// </summary>
	/// <param name="reg">BC,DE,HL,SP </param>

	/// INC BC
	void CPU::Opcode03()
	{
		bc++;
		pc++;
		cycleCount += 8;
	}

	/// INC DE
	void CPU::Opcode13()
	{
		de++;
		pc++;
		cycleCount += 8;

	}

	/// INC HL
	void CPU::Opcode23()
	{
		hl++;
		pc++;
		cycleCount += 8;

	}

	/// INC SP
	void CPU::Opcode33()
	{
		sp++;
		pc++;
		cycleCount += 8;

	}


#pragma endregion

#pragma region 4. DEC nn
	/// <summary>
	/// Decrement register nn. 
	/// </summary>
	/// <param name="reg">BC,DE,HL,SP </param>
	/// DEC BC
	void CPU::Opcode0B()
	{
		bc--;
		pc++;
		cycleCount += 8;

	}

	/// DEC DE
	void CPU::Opcode1B()
	{
		de--;
		pc++;
		cycleCount += 8;

	}

	/// DEC HL
	void CPU::Opcode2B()
	{
		hl--;
		pc++;
		cycleCount += 8;

	}

	/// DEC SP
	void CPU::Opcode3B()
	{
		sp--;
		pc++;
		cycleCount += 8;

	}
#pragma endregion

#pragma endregion

#pragma region Miscellaneous

#pragma region 1. SWAP n
	/// <summary>
	/// Swap upper & lower nibles of n.
	///	Flags affected :
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Reset.
	///		C - Reset.
	/// </summary>
	/// <param name="n"> A, B, C, D, E, H, L, (HL)</param>
	void CPU::Swap(u8 & n)
	{
		u8 upperNibble = (n >> 4) & 0xF;
		u8 lowerNibble = n & 0xF;
		u8 result = (lowerNibble << 4) | upperNibble;
		n = result;

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);
		Utility::SetFlags(af.Lo, CPUFlags::C, false);
	}

	/// SWAP A
	void CPU::OpcodeCB_37()
	{
		Swap(af.Hi);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP B
	void CPU::OpcodeCB_30()
	{
		Swap(bc.Hi);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP C
	void CPU::OpcodeCB_31()
	{
		Swap(bc.Lo);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP D
	void CPU::OpcodeCB_32()
	{
		Swap(de.Hi);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP E
	void CPU::OpcodeCB_33()
	{
		Swap(de.Lo);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP H
	void CPU::OpcodeCB_34()
	{
		Swap(hl.Hi);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP L
	void CPU::OpcodeCB_35()
	{
		Swap(hl.Lo);
		pc += 2;
		cycleCount += 8;
	}
	/// SWAP (HL)
	void CPU::OpcodeCB_36()
	{
		u8 value = mmu.Read(hl.Value);
		Swap(value);
		mmu.Write(hl.Value, value);
		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 2. DAA
	/// Decimal adjust register A.
	///	This instruction adjusts register A so that the
	///	correct representation of Binary Coded Decimal(BCD)
	///	is obtained.
	///	Flags affected :
	///		Z - Set if register A is zero.
	///		N - Not affected.
	///		H - Reset.
	///		C - Set or reset according to operation.
	void CPU::Opcode27()
	{
		u8 a = af.Hi;
		u8 f = af.Lo;

		if (Utility::IsFlagSet(f, CPUFlags::N))
		{
			if (Utility::IsFlagSet(f, CPUFlags::H) || (a & 0xF) > 9)
			{
				a += 0x06;
			}

			if (Utility::IsFlagSet(f, CPUFlags::C) || a > 0x9F)
			{
				a += 0x60;
			}
		}
		else
		{
			if (Utility::IsFlagSet(f, CPUFlags::H))
			{
				a = (a - 6) & 0xFF;
			}

			if (Utility::IsFlagSet(f, CPUFlags::C))
			{
				a -= 0x60;
			}
		}		


		Utility::SetFlags(f, CPUFlags::H, false);

		if ((a & 0x100) == 0x100)
		{
			Utility::SetFlags(f, CPUFlags::C, true);
		}

		if (a == 0)
		{
			Utility::SetFlags(f, CPUFlags::Z, true);
		}


		af.Hi = a;

		pc++;
		cycleCount += 4;
	}
	/*
	
This is from my (C#) GB emu, originally based on code posted by Blarrg and passes his GB cpu tests. 

Code:
private void Daa()
{
    int a = _regs.A;

    if (!_regs.F.HasFlag(Flags.N))
    {
        if (_regs.F.HasFlag(Flags.H) || (a & 0xF) > 9)
            a += 0x06;

        if (_regs.F.HasFlag(Flags.C) || a > 0x9F)
            a += 0x60;
    }
    else
    {
        if (_regs.F.HasFlag(Flags.H))
            a = (a - 6) & 0xFF;

        if (_regs.F.HasFlag(Flags.C))
            a -= 0x60;
    }

    _regs.F &= ~(Flags.H | Flags.Z);

    if ((a & 0x100) == 0x100)
        _regs.F |= Flags.C;

    a &= 0xFF;

    if (a == 0)
        _regs.F |= Flags.Z;

    _regs.A = (byte)a;
}
	*/

#pragma endregion

#pragma region 3. CPL
	/* 
	CPL
	Complement A register. (Flip all bits.)
 	Flags affected:
		 Z - Not affected.
		 N - Set.
		 H - Set.
		 C - Not affected.
	*/
	void CPU::Opcode2F()
	{
		af.Hi = ~af.Hi;

		Utility::SetFlags(af.Lo, CPUFlags::N, true);
		Utility::SetFlags(af.Lo, CPUFlags::H, true);

		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 4. CCF
	/*
	Complement carry flag.
	 If C flag is set, then reset it.
	 If C flag is reset, then set it.
	Flags affected:
	 Z - Not affected.
	 N - Reset.
	 H - Reset.
	 C - Complemented.
	*/
	void CPU::Opcode3F()
	{
		bool setFlag = (Utility::IsFlagSet(af.Lo, CPUFlags::C)) ? false : true;

		Utility::SetFlags(af.Lo, CPUFlags::C, setFlag);
		Utility::SetFlags(af.Lo, CPUFlags::N, false); 
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 5. SCF
	/*
	Description:
	 Set Carry flag.
	Flags affected:
	 Z - Not affected.
	 N - Reset.
	 H - Reset.
	 C - Set.	
	*/
	void CPU::Opcode37()
	{
		Utility::SetFlags(af.Lo, CPUFlags::C, true);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		pc++;
		cycleCount += 4;
	}
#pragma endregion 

#pragma region 6. NOP
	// NOP
	void CPU::Opcode00()
	{
		// just do nothing..
		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 7. HALT
	/// Description :
	///		Power down CPU until an interrupt occurs.Use this
	///		when ever possible to reduce energy consumption.
	void CPU::Opcode76()
	{
		halt = true;
		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 8. STOP
	/// Description :
	///		Halt CPU & LCD display until button pressed.
	void CPU::Opcode10()
	{
		stop = true;
		u8 value = mmu.Read(pc + 1);
		/*
		// value must be 0x00
		if(value != 0x00)
		{
			// corrupted stop
		}
		*/
		pc += 2;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 9. DI
	/// 
	/// This instruction disables interrupts but not
	/// immediately.Interrupts are disabled after
	/// instruction after DI is executed.
	void CPU::OpcodeF3()
	{
		disableInterrupts = true;
		pc++;
		cycleCount += 4;
	}

#pragma endregion

#pragma region 10. EI
	/// Enable interrupts.This intruction enables interrupts
	/// but not immediately.Interrupts are enabled after
	/// instruction after EI is executed.
	void CPU::OpcodeFB()
	{
		enableInterrupts = true;
		pc++;
		cycleCount += 4;
	}
#pragma endregion
#pragma endregion

#pragma region  Rotates & Shifts

#pragma region 1. RLCA
	/*
	Rotate A left. Old bit 7 to Carry flag.
	Flags affected:
		 Z - Reset.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 7 data. 
	*/
	void CPU::Opcode07()
	{
		u8 bit7 = af.Hi & 0x80;

		u8 result = af.Hi << 1;
		
		// was bit 7 set?
		if (bit7 == 1)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
			// since bit 7 was set, we need to set bit 0 since this is a rotate operation
			result |= bit7;
		}
		
		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		af.Hi = result;

		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 2. RLA
	/* Rotate A left through Carry flag.
	Flags:
	Z: 0
	N: 0
	H: 0
	C: Set according to result.
	*/
	void CPU::Opcode17()
	{
		u8 bit7 = af.Hi & 0x80;
		u8 carry = (u8)Utility::IsFlagSet(af.Lo, CPUFlags::C);

		u8 result = af.Hi << 1;
		result |= carry;

		// was bit 7 set?
		if (bit7 == 1)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		af.Hi = result;

		pc++;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 3. RRCA
	/* Rotate A right. Old bit 0 to Carry flag.
		Flags affected:
		 Z - Reset.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data.
	*/
	void CPU::Opcode0F()
	{
		u8 bit0 = af.Hi & 0x01;
		
		u8 result = af.Hi >> 1;

		if (bit0)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
			
			result = bit0 << 7 | result;
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		af.Hi = result;

		pc++;
		cycleCount += 4;
	}

#pragma endregion

#pragma region 4. RRA
	/* Rotate A right through Carry flag.
		Flags affected:
		 Z - Reset.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data.	
	*/
	void CPU::Opcode1F()
	{
		u8 bit0 = af.Hi & 0x01;
		u8 carry = Utility::IsFlagSet(af.Lo, CPUFlags::C);

		u8 result = af.Hi >> 1;

		if (bit0)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
		}

		result = carry << 7 | result;

		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		af.Hi = result;

		pc++;
		cycleCount += 4;
	}

#pragma endregion

#pragma region 5. RLC n
	/* Description :
		Rotate n left. Old bit 7 to Carry flag.
			Use with :
		n = A, B, C, D, E, H, L, (HL)
			Flags affected :
		Z - Set if result is zero.
		N - Reset.
		H - Reset.
		C - Contains old bit 7 data.
	*/
	void CPU::RLCn(u8 & n)
	{
		u8 bit7 = n & 0x80;

		u8 result = n << 1;

		// was bit 7 set?
		if (bit7 == 1)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
			// since bit 7 was set, we need to set bit 0 since this is a rotate operation
			result |= bit7;
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// RLC A
	void CPU::OpcodeCB_07()
	{
		RLCn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RLC B
	void CPU::OpcodeCB_00()
	{
		RLCn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RLC C
	void CPU::OpcodeCB_01()
	{
		RLCn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RLC D
	void CPU::OpcodeCB_02()
	{
		RLCn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RLC E
	void CPU::OpcodeCB_03()
	{
		RLCn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RLC H
	void CPU::OpcodeCB_04()
	{
		RLCn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RLC L
	void CPU::OpcodeCB_05()
	{
		RLCn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RLC (HL)
	void CPU::OpcodeCB_06()
	{
		u8 value = mmu.Read(hl.Value);
		RLCn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 6. RL n
	/*
		Description:
		 Rotate n left through Carry flag.
		Use with:
		 n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 7 data
	*/
	void CPU::RLn(u8 & n)
	{
		u8 bit7 =n & 0x80;
		u8 carry = (u8)Utility::IsFlagSet(af.Lo, CPUFlags::C);

		u8 result = n << 1;
		result |= carry;

		// was bit 7 set?
		if (bit7 == 1)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// RL A
	void CPU::OpcodeCB_17()
	{
		RLn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RL B
	void CPU::OpcodeCB_10()
	{
		RLn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RL C
	void CPU::OpcodeCB_11()
	{
		RLn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RL D
	void CPU::OpcodeCB_12()
	{
		RLn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RL E
	void CPU::OpcodeCB_13()
	{
		RLn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RL H
	void CPU::OpcodeCB_14()
	{
		RLn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RL L
	void CPU::OpcodeCB_15()
	{
		RLn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RL (HL)
	void CPU::OpcodeCB_16()
	{
		u8 value = mmu.Read(hl.Value);
		RLn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 7. RRC n
	/* Rotate n right. Old bit 0 to Carry flag.
		Use with:
		n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data.	
	*/
	void CPU::RRCn(u8 & n)
	{
		u8 bit0 = n & 0x01;

		u8 result = n >> 1;

		if (bit0)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);

			result = bit0 << 7 | result;
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, false);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// RRC A
	void CPU::OpcodeCB_0F()
	{
		RRCn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RRC B
	void CPU::OpcodeCB_08()
	{
		RRCn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RRC C
	void CPU::OpcodeCB_09()
	{
		RRCn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RRC D
	void CPU::OpcodeCB_0A()
	{
		RRCn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RRC E
	void CPU::OpcodeCB_0B()
	{
		RRCn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RRC H
	void CPU::OpcodeCB_0C()
	{
		RRCn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}
	// RRC L
	void CPU::OpcodeCB_0D()
	{
		RRCn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}
	// RRC (HL)
	void CPU::OpcodeCB_0E()
	{
		u8 value = mmu.Read(hl.Value);
		RRCn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 8. RR n
	/* Rotate n right through Carry flag.
		Use with:
		 n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data
	*/
	void CPU::RRn(u8 & n)
	{
		u8 bit0 = n & 0x01;
		u8 carry = Utility::IsFlagSet(af.Lo, CPUFlags::C);

		u8 result = n >> 1;

		if (bit0)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
		}

		result = carry << 7 | result;

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// RR A
	void CPU::OpcodeCB_1F()
	{
		RRn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RR B
	void CPU::OpcodeCB_18()
	{
		RRn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RR C
	void CPU::OpcodeCB_19()
	{
		RRn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RR D
	void CPU::OpcodeCB_1A()
	{
		RRn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RR E
	void CPU::OpcodeCB_1B()
	{
		RRn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RR H
	void CPU::OpcodeCB_1C()
	{
		RRn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// RR L
	void CPU::OpcodeCB_1D()
	{
		RRn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// RR (HL)
	void CPU::OpcodeCB_1E()
	{
		u8 value = mmu.Read(hl.Value);
		RRn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}


#pragma endregion

#pragma region 9. SLA n
	/*Shift n left into Carry. LSB of n set to 0.
		C <- [7 <- 0] <- 0
		Use with:
		 n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 7 data.
	 */
	void CPU::SLAn(u8 & n)
	{
		u8 bit7 = n & 0x80;
		u8 result = n << 1;

		if (bit7)
		{
			Utility::SetFlags(af.Lo, CPUFlags::C, true);
		}

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::C, false);
		Utility::SetFlags(af.Lo, CPUFlags::C, false);

		n = result;
	}

	// SLA A
	void CPU::OpcodeCB_27()
	{
		SLAn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SLA B
	void CPU::OpcodeCB_20()
	{
		SLAn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SLA C
	void CPU::OpcodeCB_21()
	{
		SLAn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SLA D
	void CPU::OpcodeCB_22()
	{
		SLAn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SLA E
	void CPU::OpcodeCB_23()
	{
		SLAn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SLA H
	void CPU::OpcodeCB_24()
	{
		SLAn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SLA L
	void CPU::OpcodeCB_25()
	{
		SLAn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SLA (HL)
	void CPU::OpcodeCB_26()
	{
		u8 value = mmu.Read(hl.Value);
		SLAn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma region 10. SRA n
	/*Shift n right into Carry. MSB doesn't change.
		[7] -> [7 -> 0] -> C
		Use with:
		 n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data.
	*/
	void CPU::SRAn(u8& n)
	{
		u8 bit7 = n & 0x80;
		u8 bit0 = n & 0x01;

		u8 result = n >> 1;

		Utility::SetFlags(af.Lo, CPUFlags::C, bit0 == 1);

		result = bit7 << 7 | result;

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// SRA A
	void CPU::OpcodeCB_2F()
	{
		SRAn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRA B
	void CPU::OpcodeCB_28()
	{
		SRAn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRA C
	void CPU::OpcodeCB_29()
	{
		SRAn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRA D
	void CPU::OpcodeCB_2A()
	{
		SRAn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRA E
	void CPU::OpcodeCB_2B()
	{
		SRAn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRA H
	void CPU::OpcodeCB_2C()
	{
		SRAn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRA L
	void CPU::OpcodeCB_2D()
	{
		SRAn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRA (HL)
	void CPU::OpcodeCB_2E()
	{
		u8 value = mmu.Read(hl.Value);
		SRAn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}
#pragma endregion

#pragma region 11. SRL n
	/*Shift n right into Carry. MSB set to 0.
		0 -> [7 -> 0] -> C
		Use with:
		 n = A,B,C,D,E,H,L,(HL)
		Flags affected:
		 Z - Set if result is zero.
		 N - Reset.
		 H - Reset.
		 C - Contains old bit 0 data.
	*/
	void CPU::SRLn(u8 & n)
	{
		u8 bit0 = n & 0x01;

		u8 result = n >> 1;

		Utility::SetFlags(af.Lo, CPUFlags::C, bit0 == 1);

		result = 0 << 7 | result;

		Utility::SetFlags(af.Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, false);

		n = result;
	}

	// SRL A
	void CPU::OpcodeCB_3F()
	{
		SRLn(af.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRL B
	void CPU::OpcodeCB_38()
	{
		SRLn(bc.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRL C
	void CPU::OpcodeCB_39()
	{
		SRLn(bc.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRL D
	void CPU::OpcodeCB_3A()
	{
		SRLn(de.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRL E
	void CPU::OpcodeCB_3B()
	{
		SRLn(de.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRL H
	void CPU::OpcodeCB_3C()
	{
		SRLn(hl.Hi);

		pc += 2;
		cycleCount += 8;
	}

	// SRL L
	void CPU::OpcodeCB_3D()
	{
		SRLn(hl.Lo);

		pc += 2;
		cycleCount += 8;
	}

	// SRL (HL)
	void CPU::OpcodeCB_3E()
	{
		u8 value = mmu.Read(hl.Value);
		SRLn(value);
		mmu.Write(hl.Value, value);

		pc += 2;
		cycleCount += 16;
	}
#pragma endregion
#pragma endregion

#pragma region Bit Opcodes
#pragma region 1. BIT b,r
	/*
	BIT u3,r8
		Test bit u3 in register r8, set the zero flag if bit not set.
		Cycles: 2
		Bytes: 2
		Flags:
		Z: Set if the selected bit is 0.
		N: 0
		H: 1
	*/
	void CPU::BITbr(u8 BITbr, u8& r)
	{
		if ((BITbr >= 0) || (BITbr <= 7))
		{
			bool isSet = ((r >> BITbr) & 0x01) == 1;

			Utility::SetFlags(af.Lo, CPUFlags::Z, !isSet);
		}
		
		Utility::SetFlags(af.Lo, CPUFlags::N, false);
		Utility::SetFlags(af.Lo, CPUFlags::H, true);
	} 

	// BITbr 0, A
	void CPU::OpcodeCB_47()
	{
		BITbr(0, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, B
	void CPU::OpcodeCB_40()
	{
		BITbr(0, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, C
	void CPU::OpcodeCB_41()
	{
		BITbr(0, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, D
	void CPU::OpcodeCB_42()
	{
		BITbr(0, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, E
	void CPU::OpcodeCB_43()
	{
		BITbr(0, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, H
	void CPU::OpcodeCB_44()
	{
		BITbr(0, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, L
	void CPU::OpcodeCB_45()
	{
		BITbr(0, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 0, (HL)
	void CPU::OpcodeCB_46()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(0, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 1, A
	void CPU::OpcodeCB_4F()
	{
		BITbr(1, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, B
	void CPU::OpcodeCB_48()
	{
		BITbr(1, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, C
	void CPU::OpcodeCB_49()
	{
		BITbr(1, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, D
	void CPU::OpcodeCB_4A()
	{
		BITbr(1, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, E
	void CPU::OpcodeCB_4B()
	{
		BITbr(1, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, H
	void CPU::OpcodeCB_4C()
	{
		BITbr(1, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, L
	void CPU::OpcodeCB_4D()
	{
		BITbr(1, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 1, (HL)
	void CPU::OpcodeCB_4E()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(1, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 2, A
	void CPU::OpcodeCB_57()
	{
		BITbr(2, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, B
	void CPU::OpcodeCB_50()
	{
		BITbr(2, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, C
	void CPU::OpcodeCB_51()
	{
		BITbr(2, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, D
	void CPU::OpcodeCB_52()
	{
		BITbr(2, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, E
	void CPU::OpcodeCB_53()
	{
		BITbr(2, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, H
	void CPU::OpcodeCB_54()
	{
		BITbr(2, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, L
	void CPU::OpcodeCB_55()
	{
		BITbr(2, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 2, (HL)
	void CPU::OpcodeCB_56()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(2, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 3, A
	void CPU::OpcodeCB_5F()
	{
		BITbr(3, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, B
	void CPU::OpcodeCB_58()
	{
		BITbr(3, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, C
	void CPU::OpcodeCB_59()
	{
		BITbr(3, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, D
	void CPU::OpcodeCB_5A()
	{
		BITbr(3, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, E
	void CPU::OpcodeCB_5B()
	{
		BITbr(3, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, H
	void CPU::OpcodeCB_5C()
	{
		BITbr(3, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, L
	void CPU::OpcodeCB_5D()
	{
		BITbr(3, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 3, (HL)
	void CPU::OpcodeCB_5E()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(3, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 4, A
	void CPU::OpcodeCB_67()
	{
		BITbr(4, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, B
	void CPU::OpcodeCB_60()
	{
		BITbr(4, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, C
	void CPU::OpcodeCB_61()
	{
		BITbr(4, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, D
	void CPU::OpcodeCB_62()
	{
		BITbr(4, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, E
	void CPU::OpcodeCB_63()
	{
		BITbr(4, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, H
	void CPU::OpcodeCB_64()
	{
		BITbr(4, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, L
	void CPU::OpcodeCB_65()
	{
		BITbr(4, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 4, (HL)
	void CPU::OpcodeCB_66()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(4, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 5, A
	void CPU::OpcodeCB_6F()
	{
		BITbr(5, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, B
	void CPU::OpcodeCB_68()
	{
		BITbr(5, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, C
	void CPU::OpcodeCB_69()
	{
		BITbr(5, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, D
	void CPU::OpcodeCB_6A()
	{
		BITbr(5, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, E
	void CPU::OpcodeCB_6B()
	{
		BITbr(5, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, H
	void CPU::OpcodeCB_6C()
	{
		BITbr(5, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, L
	void CPU::OpcodeCB_6D()
	{
		BITbr(5, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 5, (HL)
	void CPU::OpcodeCB_6E()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(5, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 6, A
	void CPU::OpcodeCB_77()
	{
		BITbr(6, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, B
	void CPU::OpcodeCB_70()
	{
		BITbr(6, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, C
	void CPU::OpcodeCB_71()
	{
		BITbr(6, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, D
	void CPU::OpcodeCB_72()
	{
		BITbr(6, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, E
	void CPU::OpcodeCB_73()
	{
		BITbr(6, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, H
	void CPU::OpcodeCB_74()
	{
		BITbr(6, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, L
	void CPU::OpcodeCB_75()
	{
		BITbr(6, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 6, (HL)
	void CPU::OpcodeCB_76()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(6, value);
		pc += 2;
		cycleCount += 16;
	}
	// BITbr 7, A
	void CPU::OpcodeCB_7F()
	{
		BITbr(7, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, B
	void CPU::OpcodeCB_78()
	{
		BITbr(7, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, C
	void CPU::OpcodeCB_79()
	{
		BITbr(7, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, D
	void CPU::OpcodeCB_7A()
	{
		BITbr(7, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, E
	void CPU::OpcodeCB_7B()
	{
		BITbr(7, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, H
	void CPU::OpcodeCB_7C()
	{
		BITbr(7, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, L
	void CPU::OpcodeCB_7D()
	{
		BITbr(7, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// BITbr 7, (HL)
	void CPU::OpcodeCB_7E()
	{
		u8 value = mmu.Read(hl.Value);
		BITbr(7, value);
		pc += 2;
		cycleCount += 16;
	}
#pragma endregion
#pragma region 2. SET b,r
	/* Set bit u3 in register r8 to 1.
		Cycles: 2
		Bytes: 2
		Flags: None affected.
	*/
	void CPU::SETbr(u8 bit, u8& r)
	{
		r = (1 << bit) | r;
	}

	// SETbr 0, A
	void CPU::OpcodeCB_C7()
	{
		SETbr(0, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, B
	void CPU::OpcodeCB_C0()
	{
		SETbr(0, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, C
	void CPU::OpcodeCB_C1()
	{
		SETbr(0, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, D
	void CPU::OpcodeCB_C2()
	{
		SETbr(0, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, E
	void CPU::OpcodeCB_C3()
	{
		SETbr(0, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, H
	void CPU::OpcodeCB_C4()
	{
		SETbr(0, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, L
	void CPU::OpcodeCB_C5()
	{
		SETbr(0, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 0, (HL)
	void CPU::OpcodeCB_C6()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(0, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 1, A
	void CPU::OpcodeCB_CF()
	{
		SETbr(1, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, B
	void CPU::OpcodeCB_C8()
	{
		SETbr(1, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, C
	void CPU::OpcodeCB_C9()
	{
		SETbr(1, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, D
	void CPU::OpcodeCB_CA()
	{
		SETbr(1, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, E
	void CPU::OpcodeCB_CB()
	{
		SETbr(1, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, H
	void CPU::OpcodeCB_CC()
	{
		SETbr(1, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, L
	void CPU::OpcodeCB_CD()
	{
		SETbr(1, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 1, (HL)
	void CPU::OpcodeCB_CE()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(1, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 2, A
	void CPU::OpcodeCB_D7()
	{
		SETbr(2, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, B
	void CPU::OpcodeCB_D0()
	{
		SETbr(2, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, C
	void CPU::OpcodeCB_D1()
	{
		SETbr(2, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, D
	void CPU::OpcodeCB_D2()
	{
		SETbr(2, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, E
	void CPU::OpcodeCB_D3()
	{
		SETbr(2, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, H
	void CPU::OpcodeCB_D4()
	{
		SETbr(2, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, L
	void CPU::OpcodeCB_D5()
	{
		SETbr(2, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 2, (HL)
	void CPU::OpcodeCB_D6()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(2, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 3, A
	void CPU::OpcodeCB_DF()
	{
		SETbr(3, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, B
	void CPU::OpcodeCB_D8()
	{
		SETbr(3, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, C
	void CPU::OpcodeCB_D9()
	{
		SETbr(3, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, D
	void CPU::OpcodeCB_DA()
	{
		SETbr(3, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, E
	void CPU::OpcodeCB_DB()
	{
		SETbr(3, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, H
	void CPU::OpcodeCB_DC()
	{
		SETbr(3, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, L
	void CPU::OpcodeCB_DD()
	{
		SETbr(3, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 3, (HL)
	void CPU::OpcodeCB_DE()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(3, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 4, A
	void CPU::OpcodeCB_E7()
	{
		SETbr(4, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, B
	void CPU::OpcodeCB_E0()
	{
		SETbr(4, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, C
	void CPU::OpcodeCB_E1()
	{
		SETbr(4, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, D
	void CPU::OpcodeCB_E2()
	{
		SETbr(4, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, E
	void CPU::OpcodeCB_E3()
	{
		SETbr(4, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, H
	void CPU::OpcodeCB_E4()
	{
		SETbr(4, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, L
	void CPU::OpcodeCB_E5()
	{
		SETbr(4, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 4, (HL)
	void CPU::OpcodeCB_E6()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(4, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 5, A
	void CPU::OpcodeCB_EF()
	{
		SETbr(5, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, B
	void CPU::OpcodeCB_E8()
	{
		SETbr(5, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, C
	void CPU::OpcodeCB_E9()
	{
		SETbr(5, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, D
	void CPU::OpcodeCB_EA()
	{
		SETbr(5, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, E
	void CPU::OpcodeCB_EB()
	{
		SETbr(5, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, H
	void CPU::OpcodeCB_EC()
	{
		SETbr(5, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, L
	void CPU::OpcodeCB_ED()
	{
		SETbr(5, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 5, (HL)
	void CPU::OpcodeCB_EE()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(5, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 6, A
	void CPU::OpcodeCB_F7()
	{
		SETbr(6, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, B
	void CPU::OpcodeCB_F0()
	{
		SETbr(6, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, C
	void CPU::OpcodeCB_F1()
	{
		SETbr(6, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, D
	void CPU::OpcodeCB_F2()
	{
		SETbr(6, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, E
	void CPU::OpcodeCB_F3()
	{
		SETbr(6, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, H
	void CPU::OpcodeCB_F4()
	{
		SETbr(6, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, L
	void CPU::OpcodeCB_F5()
	{
		SETbr(6, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 6, (HL)
	void CPU::OpcodeCB_F6()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(6, value);
		pc += 2;
		cycleCount += 16;
	}
	// SETbr 7, A
	void CPU::OpcodeCB_FF()
	{
		SETbr(7, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, B
	void CPU::OpcodeCB_F8()
	{
		SETbr(7, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, C
	void CPU::OpcodeCB_F9()
	{
		SETbr(7, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, D
	void CPU::OpcodeCB_FA()
	{
		SETbr(7, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, E
	void CPU::OpcodeCB_FB()
	{
		SETbr(7, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, H
	void CPU::OpcodeCB_FC()
	{
		SETbr(7, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, L
	void CPU::OpcodeCB_FD()
	{
		SETbr(7, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// SETbr 7, (HL)
	void CPU::OpcodeCB_FE()
	{
		u8 value = mmu.Read(hl.Value);
		SETbr(7, value);
		pc += 2;
		cycleCount += 16;
	}


#pragma endregion

#pragma region 3. RES b,r
	/*Set bit u3 in register r8 to 0.
		Cycles: 2
		Bytes: 2
		Flags: None affected.
	*/
	void CPU::RESbr(u8 bit, u8& r)
	{
		r = (0 << bit) | r;
	}


	// RESbr 0, A
	void CPU::OpcodeCB_87()
	{
		RESbr(0, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, B
	void CPU::OpcodeCB_80()
	{
		RESbr(0, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, C
	void CPU::OpcodeCB_81()
	{
		RESbr(0, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, D
	void CPU::OpcodeCB_82()
	{
		RESbr(0, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, E
	void CPU::OpcodeCB_83()
	{
		RESbr(0, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, H
	void CPU::OpcodeCB_84()
	{
		RESbr(0, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, L
	void CPU::OpcodeCB_85()
	{
		RESbr(0, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 0, (HL)
	void CPU::OpcodeCB_86()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(0, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 1, A
	void CPU::OpcodeCB_8F()
	{
		RESbr(1, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, B
	void CPU::OpcodeCB_88()
	{
		RESbr(1, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, C
	void CPU::OpcodeCB_89()
	{
		RESbr(1, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, D
	void CPU::OpcodeCB_8A()
	{
		RESbr(1, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, E
	void CPU::OpcodeCB_8B()
	{
		RESbr(1, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, H
	void CPU::OpcodeCB_8C()
	{
		RESbr(1, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, L
	void CPU::OpcodeCB_8D()
	{
		RESbr(1, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 1, (HL)
	void CPU::OpcodeCB_8E()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(1, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 2, A
	void CPU::OpcodeCB_97()
	{
		RESbr(2, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, B
	void CPU::OpcodeCB_90()
	{
		RESbr(2, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, C
	void CPU::OpcodeCB_91()
	{
		RESbr(2, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, D
	void CPU::OpcodeCB_92()
	{
		RESbr(2, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, E
	void CPU::OpcodeCB_93()
	{
		RESbr(2, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, H
	void CPU::OpcodeCB_94()
	{
		RESbr(2, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, L
	void CPU::OpcodeCB_95()
	{
		RESbr(2, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 2, (HL)
	void CPU::OpcodeCB_96()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(2, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 3, A
	void CPU::OpcodeCB_9F()
	{
		RESbr(3, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, B
	void CPU::OpcodeCB_98()
	{
		RESbr(3, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, C
	void CPU::OpcodeCB_99()
	{
		RESbr(3, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, D
	void CPU::OpcodeCB_9A()
	{
		RESbr(3, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, E
	void CPU::OpcodeCB_9B()
	{
		RESbr(3, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, H
	void CPU::OpcodeCB_9C()
	{
		RESbr(3, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, L
	void CPU::OpcodeCB_9D()
	{
		RESbr(3, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 3, (HL)
	void CPU::OpcodeCB_9E()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(3, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 4, A
	void CPU::OpcodeCB_A7()
	{
		RESbr(4, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, B
	void CPU::OpcodeCB_A0()
	{
		RESbr(4, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, C
	void CPU::OpcodeCB_A1()
	{
		RESbr(4, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, D
	void CPU::OpcodeCB_A2()
	{
		RESbr(4, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, E
	void CPU::OpcodeCB_A3()
	{
		RESbr(4, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, H
	void CPU::OpcodeCB_A4()
	{
		RESbr(4, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, L
	void CPU::OpcodeCB_A5()
	{
		RESbr(4, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 4, (HL)
	void CPU::OpcodeCB_A6()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(4, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 5, A
	void CPU::OpcodeCB_AF()
	{
		RESbr(5, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, B
	void CPU::OpcodeCB_A8()
	{
		RESbr(5, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, C
	void CPU::OpcodeCB_A9()
	{
		RESbr(5, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, D
	void CPU::OpcodeCB_AA()
	{
		RESbr(5, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, E
	void CPU::OpcodeCB_AB()
	{
		RESbr(5, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, H
	void CPU::OpcodeCB_AC()
	{
		RESbr(5, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, L
	void CPU::OpcodeCB_AD()
	{
		RESbr(5, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 5, (HL)
	void CPU::OpcodeCB_AE()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(5, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 6, A
	void CPU::OpcodeCB_B7()
	{
		RESbr(6, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, B
	void CPU::OpcodeCB_B0()
	{
		RESbr(6, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, C
	void CPU::OpcodeCB_B1()
	{
		RESbr(6, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, D
	void CPU::OpcodeCB_B2()
	{
		RESbr(6, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, E
	void CPU::OpcodeCB_B3()
	{
		RESbr(6, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, H
	void CPU::OpcodeCB_B4()
	{
		RESbr(6, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, L
	void CPU::OpcodeCB_B5()
	{
		RESbr(6, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 6, (HL)
	void CPU::OpcodeCB_B6()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(6, value);
		pc += 2;
		cycleCount += 16;
	}
	// RESbr 7, A
	void CPU::OpcodeCB_BF()
	{
		RESbr(7, af.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, B
	void CPU::OpcodeCB_B8()
	{
		RESbr(7, bc.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, C
	void CPU::OpcodeCB_B9()
	{
		RESbr(7, bc.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, D
	void CPU::OpcodeCB_BA()
	{
		RESbr(7, de.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, E
	void CPU::OpcodeCB_BB()
	{
		RESbr(7, de.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, H
	void CPU::OpcodeCB_BC()
	{
		RESbr(7, hl.Hi);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, L
	void CPU::OpcodeCB_BD()
	{
		RESbr(7, hl.Lo);
		pc += 2;
		cycleCount += 8;
	}

	// RESbr 7, (HL)
	void CPU::OpcodeCB_BE()
	{
		u8 value = mmu.Read(hl.Value);
		RESbr(7, value);
		pc += 2;
		cycleCount += 16;
	}

#pragma endregion

#pragma endregion

#pragma region Jumps

#pragma region 1. JP nn
	/*
	Absolute jump to address n16.
	Cycles: 4
	Bytes: 3
	Flags: None affected.
	*/
	void CPU::OpcodeC3()
	{
		u16 address = Load16BitImmediateValue();

		pc = address;
		cycleCount += 16;
	}
#pragma endregion

#pragma region 2. JP cc,nn
	/*Jump to address n if following condition is true:
		 cc = NZ, Jump if Z flag is reset.
		 cc = Z, Jump if Z flag is set.
		 cc = NC, Jump if C flag is reset.
		 cc = C, Jump if C flag is set.
	*/
	// JP NZ, nn
	void CPU::OpcodeC2()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			u16 address = Load16BitImmediateValue();

			pc = address;
			cycleCount += 16;
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
	// JP Z, nn
	void CPU::OpcodeCA()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			u16 address = Load16BitImmediateValue();

			pc = address;
			cycleCount += 16;
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}

	// JP NC, nn
	void CPU::OpcodeD2()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			u16 address = Load16BitImmediateValue();

			pc = address;
			cycleCount += 16;
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
	// JP C, nn
	void CPU::OpcodeDA()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			u16 address = Load16BitImmediateValue();

			pc = address;
			cycleCount += 16;
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}

#pragma endregion

#pragma region 3. JP (HL)
	// Jump to address contained in HL
	void CPU::OpcodeE9()
	{
		pc = hl.Value;
		cycleCount += 4;
	}
#pragma endregion

#pragma region 4. JR n
	// Add n to current address and jump to it.
	void CPU::Opcode18()
	{
		pc += Load8BitImmediateValue();
		cycleCount += 12;
	}
#pragma endregion

#pragma region 5. JR cc,n
	/*If following condition is true then add n to current address and jump to it:
		Use with:
		 n = one byte signed immediate value
		 cc = NZ, Jump if Z flag is reset.
		 cc = Z, Jump if Z flag is set.
		 cc = NC, Jump if C flag is reset.
		 cc = C, Jump if C flag is set.
	*/
	// JR NZ,n
	void CPU::Opcode20()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			pc += Load8BitImmediateValue();
			cycleCount += 12;
		}
		else
		{
			pc += 2;
			cycleCount += 8;
		}
	}
	// JR Z,n
	void CPU::Opcode28()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			pc += Load8BitImmediateValue();
			cycleCount += 12;
		}
		else
		{
			pc += 2;
			cycleCount += 8;
		}
	}
	// JR NZ,n
	void CPU::Opcode30()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			pc += Load8BitImmediateValue();
			cycleCount += 12;
		}
		else
		{
			pc += 2;
			cycleCount += 8;
		}
	}
	// JR NZ,n
	void CPU::Opcode38()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			pc += Load8BitImmediateValue();
			cycleCount += 12;
		}
		else
		{
			pc += 2;
			cycleCount += 8;
		}
	}
#pragma endregion

#pragma endregion

#pragma region  Calls

#pragma region 1. CALL nn
	/*Push address of next instruction onto stack and then
	  jump to address nn.*/
	void CPU::OpcodeCD()
	{
		u16 address = Load16BitImmediateValue();
		pc += 3;
		mmu.Push(sp, pc.Value);

		pc = address;
		cycleCount += 24;
	}
#pragma endregion

#pragma region 2. CALL cc,nn
	/*Call address n if following condition is true:
		 cc = NZ, Call if Z flag is reset.
		 cc = Z, Call if Z flag is set.
		 cc = NC, Call if C flag is reset.
		 cc = C, Call if C flag is set.
		Use with:
		 nn = two byte immediate value. (LS byte first.)*/
	// CALL NZ, nn
	void CPU::OpcodeC4()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			OpcodeCD(); // Call
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
	// CALL Z, nn
	void CPU::OpcodeCC()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			OpcodeCC(); // Call
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
	// CALL NC, nn
	void CPU::OpcodeD4()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			OpcodeCD(); // Call
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
	// CALL C, nn
	void CPU::OpcodeDC()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			OpcodeCD(); // Call
		}
		else
		{
			pc += 3;
			cycleCount += 12;
		}
	}
#pragma endregion

#pragma endregion

#pragma region Restarts

#pragma region 1. RST n
	/* Push present address onto stack.
		Jump to address $0000 + n.
		Use with :
			n = $00, $08, $10, $18, $20, $28, $30, $38
	*/
	// RST 00H
	void CPU::OpcodeC7()
	{
		pc = 0x0000 + 0x00;
		cycleCount += 16;
	}
	// RST 08H
	void CPU::OpcodeCF()
	{
		pc = 0x0000 + 0x08;
		cycleCount += 16;
	}
	// RST 10H
	void CPU::OpcodeD7()
	{
		pc = 0x0000 + 0x10;
		cycleCount += 16;
	}
	// RST 18H
	void CPU::OpcodeDF()
	{
		pc = 0x0000 + 0x18;
		cycleCount += 16;
	}
	// RST 20H
	void CPU::OpcodeE7()
	{
		pc = 0x0000 + 0x20;
		cycleCount += 16;
	}
	// RST 28H
	void CPU::OpcodeEF()
	{
		pc = 0x0000 + 0x28;
		cycleCount += 16;
	}
	// RST 30H
	void CPU::OpcodeF7()
	{
		pc = 0x0000 + 0x30;
		cycleCount += 16;
	}
	// RST 38H
	void CPU::OpcodeFF()
	{
		pc = 0x0000 + 0x38;
		cycleCount += 16;
	}
#pragma endregion

#pragma endregion

#pragma region Returns

#pragma region 1. RET

	// Pop two bytes from stack & jump to that address.	
	void CPU::OpcodeC9()
	{
		u8 address = mmu.Pop(sp);
		pc = address;
		cycleCount += 16;
	}
#pragma endregion

#pragma region 2. RET cc
	/*Return if following condition is true:
	Use with:
	cc = NZ, Return if Z flag is reset.
	cc = Z, Return if Z flag is set.
	cc = NC, Return if C flag is reset.
	cc = C, Return if C flag is set.
	*/
	// RET NZ
	void CPU::OpcodeC0()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			u8 address = mmu.Pop(sp);
			pc = address;
			cycleCount += 20;
		}
		else
		{
			pc++;
			cycleCount += 8;
		}
	}
	// RET Z
	void CPU::OpcodeC8()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::Z))
		{
			u8 address = mmu.Pop(sp);
			pc = address;
			cycleCount += 20;
		}
		else
		{
			pc++;
			cycleCount += 8;
		}
	}// RET NC
	void CPU::OpcodeD0()
	{
		if (!Utility::IsFlagSet(af.Lo, CPUFlags::N))
		{
			u8 address = mmu.Pop(sp);
			pc = address;
			cycleCount += 20;
		}
		else
		{
			pc++;
			cycleCount += 8;
		}
	}// RET C
	void CPU::OpcodeD8()
	{
		if (Utility::IsFlagSet(af.Lo, CPUFlags::C))
		{
			u8 address = mmu.Pop(sp);
			pc = address;
			cycleCount += 20;
		}
		else
		{
			pc++;
			cycleCount += 8;
		}
	}
#pragma endregion

#pragma region 3. RETI
	// Pop two bytes from stack & jump to that address then enable interrupts.
	void CPU::OpcodeD9()
	{
		u8 address = mmu.Pop(sp);
		pc = address;
		enableInterrupts = true;
		cycleCount += 16;
	}
#pragma endregion


#pragma endregion

#pragma region Not Existant Opcodes
	void CPU::OpcodeD3()
	{

	}
	void CPU::OpcodeDB()
	{

	}
	void CPU::OpcodeDD()
	{

	}
	void CPU::OpcodeE3()
	{

	}
	void CPU::OpcodeE4()
	{

	}
	void CPU::OpcodeEB()
	{

	}
	void CPU::OpcodeEC()
	{

	}
	void CPU::OpcodeED()
	{

	}
	void CPU::OpcodeF4()
	{

	}
	void CPU::OpcodeFC()
	{

	}
	void CPU::OpcodeFD()
	{

	}
#pragma endregion

	void CPU::OpcodeCB()
	{
		u8 opcode = Load8BitImmediateValue();
		OpcodeFunction opcodeMethod = OpcodeCBs[opcode];
		(this->*opcodeMethod)();
	}
}
