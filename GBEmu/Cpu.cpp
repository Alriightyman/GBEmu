#include "Cpu.h"

Cpu::Cpu() 
	: m_PC(0x100),m_B(0),m_C(0x13),m_D(0),
	m_E(0xD8),m_H(0x1),m_L(0x4D),m_SP(0xFFFE),
	m_A(0x0),m_F(0x1),m_cycles(0)
{

}

bool Cpu::Initialize()
{

	return true;
}

void Cpu::Run()
{

}
#pragma region Commands
// most of the opcodes are created via macros
// ------------------------------------------
// 8-Bit Loads
// ------------------------------------------
// LD nn,n
// nn = B,C,D,E,H,L
// n = 8-bit immediate value
// opcodes - 06, 0E, 16,1E,26,2E
#define ld_nn_n(r) 					\
		m_PC++;						\
		r = mem[0xFF00 + m_PC];		\
		return  8;	
// LD r1,r2
// r1,r2 =A, B,C,D,E,H,L
// opcodes - 7F,78,79,7A,7B,7C,40,41,42,43,44,45,48,49,4A
//			 4B,4C,4D,50,51,52,53,54,55,58,59,5A,5B,5C,5D,
//			 60,61,62,63,64,65,68,69,6A,6B,6C,6D
#define ld_r1r2(r1,r2)			\
		r1 = r2;				\
		return 4;
// LD r1,(hl)
// r1 =A, B,C,D,E,H,L
// opcodes - 7E,46,4E,56,5E,66,6E
#define ld_r1hl(r1)								\
		r1 = mem[0xFF00 + ((m_H << 8) | m_L)];	\
		return 8;
// LD (hl),r
// r = B,C,D,E,L,H,n
// opcodes - 70,71,72,73,74,75
#define ld_hlr(r)							\
	mem[0xFF00 + ((m_H << 8 ) | m_L)] = r;	\
	return 8;
// LD (hl),n
// n = 8-bit immediate
// opcodes - 36
#define ld_hln(n)							\
	mem[0xFF00 + ((m_H << 8) | m_L)] = n;	\
	return 12;
// LD a,n
// n = A,B,C,D,E,H,L,8-bit value
// opcodes - 7F,78,79,7A,7B,7C,7D
#define ld_an(n)							\
	m_A = n;								\
	return 4;
// LD a,(r1r2)
// r1 = B,D,H
// r2 = C,E,L
// opcodes - 7F,78,79,7A,7B,7C,7D
#define ld_aRegAddr(r1,r2)					\
	m_A = mem[0xFF00 + ((r1 >> 8) | r2)];	\
	return 8;




#pragma endregion


#ifdef FNCPTRS
// ==========================================
// function implementations
// ==========================================
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
/*	
	m_PC++;
	m_B = mem[m_PC++];
	return 8;
*/
	ld_nn_n(m_B);
}
// 1 byte, 4 cycles, 0 0 0 C			// 07
uint Cpu::RLCA(Memory& mem)
{
	m_PC++;
	return 4;
}
#endif
