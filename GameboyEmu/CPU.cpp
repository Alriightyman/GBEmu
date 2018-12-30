#include "CPU.h"
#include "Utility.h"

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

}