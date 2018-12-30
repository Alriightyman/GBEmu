#pragma once
#include "TypesDef.h"

namespace Gameboy
{
	class MMU
	{
	private:
		u8 memory[0xFFFF];

	public:
		MMU();
		~MMU();

		u8 Read(u16 address);
		void Write(u16 address, u8 value);
		void Write(u16 address, u16 value);
	};
}
