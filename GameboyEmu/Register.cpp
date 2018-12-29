#include "Register.h"

namespace Gameboy
{

	Register::Register() : Value(0x00)
	{
	}

	u16 Register::operator=(int lhs)
	{
		this->Value = lhs;
		return Value;
	}

	u16 Register::operator+=(int lhs)
	{
		Value += lhs;
		return Value;
	}

	u16 Register::operator-=(int lhs)
	{
		Value -= lhs;
		return Value;
	}

	u16 Register::operator+(int rhs)
	{
		u16 result = this->Value + rhs;
		return result;
	}

	u16 Register::operator-(int rhs)
	{
		u16 result = this->Value - rhs;
		return result;
	}


	u16 Register::operator++()
	{
		Value++;
		return Value;
	}
	u16 Register::operator--()
	{
		Value--;
		return Value;
	}
	u16 Register::operator++(int)
	{
		++Value;
		return Value;
	}
	u16 Register::operator--(int)
	{
		--Value;
		return Value;
	}
}