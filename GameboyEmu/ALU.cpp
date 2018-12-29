#include "ALU.h"
#include "Utility.h"
#include "Register.h"

namespace Gameboy
{

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

		Utility::SetFlags(af->Lo, Utility::Flags::Z, af->Hi + n == 0);
		Utility::SetFlags(af->Lo, Utility::Flags::N, false);
		Utility::SetFlags(af->Lo, Utility::Flags::H, Utility::IsHalfCarry(af->Hi, n));
		Utility::SetFlags(af->Lo, Utility::Flags::C, Utility::IsFullCarry(af->Hi, n));

		af->Hi = result;
	}

	void ALU::Adc( u8 n)
	{
		u8 carry = Utility::IsFlagSet(af->Lo, Utility::Flags::C) ? 1 : 0;
		int result = af->Hi + n + carry;

		Utility::SetFlags(af->Lo, Utility::Flags::Z, af->Hi + n + carry == 0);
		Utility::SetFlags(af->Lo, Utility::Flags::N, false);
		Utility::SetFlags(af->Lo, Utility::Flags::H, (af->Hi & 0xF) + (n & 0xF) + carry > 0xF);
		Utility::SetFlags(af->Lo, Utility::Flags::C, result > 0xFF);

		af->Hi = result;
	}

	void ALU::Sub(u8 n)
	{
		int result = af->Hi - n;

	}

	/// <summary>
	/// Compare A with n. This is basically an A - n subtraction instruction but the results are thrown away.
	/// FLAGS AFFECTED:
	/// Z - Set if result is zero. (Set if A = n.)
	/// N - Set.
	///	H - Set if no borrow from bit 4.
	///	C - Set for no borrow. (Set if A < n.)
	/// </summary>
	/// <param name="a">Register A</param>
	/// <param name="n"> Register B,C,D,E,H,L, address of (HL), or any immediate value</param>
	void ALU::CP(u8 & a, u8 n)
	{
		u8 result = a - n;

		Utility::SetFlags(af->Lo, Utility::Flags::Z, (a == n));
		Utility::SetFlags(af->Lo, Utility::Flags::N, true);
		Utility::SetFlags(af->Lo, Utility::Flags::, true);
	}
}