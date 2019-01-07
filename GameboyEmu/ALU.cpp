#include "ALU.h"
#include "Utility.h"
#include "Register.h"

namespace Gameboy
{

	using CPUFlags = Utility::Flags;

	ALU::ALU()
	{
	}


	ALU::~ALU()
	{
	}	

	void ALU::Initialize(Register* AF)
	{
		af = AF;
	}	
	/// <summary>
	/// Add n to a
	///Flags affected:
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Set if carry from bit 3.
	///		C - Set if carry from bit 7.
	/// </summary>
	/// <param name="a">a.</param>
	/// <param name="n">The n.</param>
	void ALU::Add(u8 n)
	{
		u8 result = af->Hi + n;

		Utility::SetFlags(af->Lo, CPUFlags::Z, af->Hi + n == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfCarry(af->Hi, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, Utility::IsFullCarry(af->Hi, n));

		af->Hi = result;
	}

	/// <summary>
	///	Add n to HL.
	///	Flags affected :
	///		Z - Not affected.
	///		N - Reset.
	///		H - Set if carry from bit 11.
	///		C - Set if carry from bit 15.
	/// </summary>
	/// <param name="a">HL Register</param>
	/// <param name="n">BC, DE, HL, SP</param>
	void ALU::Add(u16 & hl, u16 n)
	{
		int result = hl + n;

		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfCarry16(af->Hi, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, Utility::IsFullCarry16(af->Hi, n));
		hl = result;
	}

	/// <summary>
	/// Add n to Stack Pointer(SP).
	/// Flags affected :
	///		Z - Reset.
	/// 	N - Reset.
	/// 	H - Set or reset according to operation.
	/// 	C - Set or reset according to operation.
	/// </summary>
	/// <param name="a">The Stack Pointer</param>
	/// <param name="n">one byte signed immediate value</param>
	void ALU::AddSP(u16 & sp, s8 n)
	{
		int value = sp + n;
		Utility::SetFlags(af->Lo, CPUFlags::Z, false);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfCarry(sp, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, Utility::IsFullCarry(sp, n));
		sp = value;
	}

	void ALU::Adc( u8 n)
	{
		u8 carry = Utility::IsFlagSet(af->Lo, CPUFlags::C) ? 1 : 0;
		int result = af->Hi + n + carry;

		Utility::SetFlags(af->Lo, CPUFlags::Z, af->Hi + n + carry == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, (af->Hi & 0xF) + (n & 0xF) + carry > 0xF);
		Utility::SetFlags(af->Lo, CPUFlags::C, result > 0xFF);

		af->Hi = result;
	}

	void ALU::Sub(u8 n)
	{
		int result = af->Hi - n;

		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, true);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfBorrow(af->Hi, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, n > af->Hi);

		af->Hi = result;
	}

	void ALU::Sbc(u8 n)
	{
		u8 carry = Utility::IsFlagSet(af->Lo, CPUFlags::C);
		int result = af->Hi - n - carry;

		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, true);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfBorrow(af->Hi, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, n > af->Hi);
	}

	/// Logically AND n with A, result in A.
	///	Flags affected :
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Set.
	///		C - Reset.
	/// <param name="n">A,B,C,D,E,H,L,(HL),#</param>
	void ALU::And(u8 n)
	{
		int result = af->Hi & n;

		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, true);
		Utility::SetFlags(af->Lo, CPUFlags::C, false);
		
		af->Lo = result;
	}

	/// <summary>
	/// Logical exclusive OR n with register A, result in A.
	///	Flags affected :
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Reset.
	///		C - Reset.
	/// </summary>
	/// <param name="n">A,B,C,D,E,H,L,(HL),#</param>
	void ALU::XOR(u8 n)
	{
		int result = af->Hi ^ n;
		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, false);
		Utility::SetFlags(af->Lo, CPUFlags::C, false);

		af->Hi = result;
	}

	/// <summary>
	/// Logical OR n with register A, result in A.
	/// Flags affected:
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Reset.
	///		C - Reset.
	/// </summary>
	/// <param name="n">A,B,C,D,E,H,L,(HL),#</param>
	void ALU::OR(u8 n)
	{
		int result = af->Hi | n;
		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, false);
		Utility::SetFlags(af->Lo, CPUFlags::C, false);

		af->Hi = result;
	}

	/// <summary>
	/// Compare A with n. This is basically an A - n subtraction instruction but the results are thrown away.
	/// FLAGS AFFECTED:
	/// Z - Set if result is zero. (Set if A = n.)
	/// N - Set.
	///	H - Set if no borrow from bit 4.
	///	C - Set for no borrow. (Set if A < n.)
	/// </summary>
	/// <param name="n"> Register B,C,D,E,H,L, address of (HL), or any immediate value</param>
	void ALU::CP(u8 n)
	{
		u8 result = af->Hi - n;

		Utility::SetFlags(af->Lo, CPUFlags::Z, (af->Hi == 0));
		Utility::SetFlags(af->Lo, CPUFlags::N, true);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfBorrow(af->Hi, n));
		Utility::SetFlags(af->Lo, CPUFlags::C, af->Hi < n);
	}

	/// <summary>
	///	Increment register n.		
	///	Flags affected:
	///		Z - Set if result is zero.
	///		N - Reset.
	///		H - Set if carry from bit 3.
	///		C - Not affected.
	/// </summary>
	/// <param name="n">A,B,C,D,E,H,L,(HL)</param>
	void ALU::Inc(u8& reg)
	{
		int result = reg + 1;
		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, false);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfCarry(reg, 1));

		reg = result;
	}

	/// <summary>
	///	Decrement register n.		
	///	Flags affected:
	///		Z - Set if result is zero.
	///		N - Set.
	///		H - Set if no borrow from bit 4..
	///		C - Not affected.
	/// </summary>
	/// <param name="n">A,B,C,D,E,H,L,(HL)</param>
	void ALU::Dec(u8 & reg)
	{
		int result = reg - 1;
		Utility::SetFlags(af->Lo, CPUFlags::Z, result == 0);
		Utility::SetFlags(af->Lo, CPUFlags::N, true);
		Utility::SetFlags(af->Lo, CPUFlags::H, Utility::IsHalfBorrow(reg, 1));

		reg = result;
	}
}