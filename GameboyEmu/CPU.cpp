#include "CPU.h"
#include "Utility.h"

namespace Gameboy
{
	///
	CPU::CPU() : cycleCount(0x00)
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

#pragma region 5. LD A,(C)	// 5. LD A,(C)
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

#pragma region 6. LD (C),A	// 6. LD (C),A
	// Description :
	//		Put A into address $FF00 + register C.	void CPU::OpcodeE2()
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
	//	 		n = one byte immediate value.	void CPU::OpcodeE0()
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
	//		   n = one byte immediate value.	void CPU::OpcodeF0()
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

		Utility::SetFlags(af.Lo, Utility::Flags::Z, false);
		Utility::SetFlags(af.Lo, Utility::Flags::N, false);
		Utility::SetFlags(af.Lo, Utility::Flags::H, Utility::IsHalfCarry16(sp.Value, immediateValue));
		Utility::SetFlags(af.Lo, Utility::Flags::C, Utility::IsFullCarry16(sp.Value, immediateValue));
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
	///			nn = AF, BC, DE, HL	///</ summary>	
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

#pragma region 2. ADC A,n		/// <summary>
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
		alu.Sub()
	}
#pragma endregion
#pragma endregion 
}
