#include "Cpu.h"

Cpu::Cpu() 
	: m_PC(0x100),m_B(0),m_C(0x13),m_D(0),
	m_E(0xD8),m_H(0x1),m_L(0x4D),m_SP(0xFFFE),
	m_A(0x0),m_F(0x1),m_cycles(0)
{

}

#pragma region Commands
// 1 byte, 4 cycles						// 00
uint Cpu::NOP(Memory& mem)				
{
	m_PC++; 
	return 4;
}
// 3 bytes, 12 cycles					// 01
uint Cpu::LD_BCd16(Memory& mem)			
{
	
	m_PC++;
	m_B = mem[m_PC] & 0xFF;
	m_PC++;
	m_C = mem[m_PC + 1] & 0xFF;
	m_PC++;
	return 12;
}
// 1 byte, 8 cycles						// 02
uint Cpu::LD_addrBC_A(Memory& mem)		
{
	mem[(m_B << 8) | m_C] = m_A;
	m_PC++;
	return 8;
}
// 1 byte, 8 cycles						// 03
uint Cpu::INC_BC(Memory& mem)			
{
	ushort d16 = ( m_B << 8 ) | m_C;
	d16++;
	m_B = (d16 >> 8) & 0xFF;
	m_C = d16 & 0xFF;
	m_PC++;
	return 8;
}
// 1 byte, 4 cycles, Z 0 H -			// 04
uint Cpu::INC_B(Memory& mem)			
{
	byte carry = m_B & 0xF;
	m_B++;
	if (m_B == 0)
		SetFlagBit(ZFlag);
	if (carry == 0xF)
		SetFlagBit(HFlag);

	ClearFlagBit(NFlag);

	return 4;
}
// 1 byte, 4 cycles, Z 1 H -			// 05
uint Cpu::DEC_B(Memory& mem)			
{
	byte carry = m_B & 0xF;
	m_B--;
	// if B is zero
	if (m_B == 0)
		SetFlagBit(ZFlag);
	// if no borrow from bit 4
	if (carry != 0)
		SetFlagBit(HFlag);

	SetFlagBit(NFlag);

	return 4;
}
// 2 bytes, 8 cycles					// 06
uint Cpu::LD_Bd8(Memory& mem)			
{
	m_PC++;
	m_B = mem[m_PC++];

	return 8;
}
// 1 byte, 4 cycles, 0 0 0 C			// 07
uint Cpu::RLCA(Memory& mem)
{
	m_PC++;
	return 4;
}
#pragma endregion