#include "Cpu.h"

Cpu::Cpu() 
	: m_PC(0x100),m_B(0),m_C(0x13),m_D(0),
	m_E(0xD8),m_H(0x1),m_L(0x4D),m_SP(0xFFFE),
	m_A(0x0),m_cycles(0)
{

}

bool Cpu::Initialize()
{

	return true;
}

void Cpu::Run(Memory& mem)
{
	byte* opcode = &mem[m_PC];

	switch (*opcode)
	{
	case 0x00: // nop - - - -
		{
			m_cycles += 4;
		}
		break;
	case 0x01: // ld bc,d16 - - - -
		{
			m_B = opcode[1];
			m_C = opcode[2];
			m_PC += 2;
			m_cycles += 12;
		}
		break;
	case 0x02: // ld (bc),a - - - -
		{
			mem[((m_B << 8) | m_C)] = m_A;	
			m_cycles +=  8; 
		}
		break;
	case 0x03: // inc BC - - - -
		{
			short answer = (m_B << 8) | m_C;
			answer++;
			m_B = (answer >> 8) & 0xF;
			m_C = answer & 0xF;
			m_cycles += 8;
		}
		break;
	case 0x04: // inc b z 0 h -
		{
			short answer = m_B + 1;
			short hc = (m_B & 0xFF) + 1;
			m_F.z = ((answer & 0xFF) == 0);
			m_F.n = 0;
			m_F.h = ((hc & 0xF) == 0 && m_B != 0xFF);
			m_B = answer & 0xFF;
			m_cycles += 4;
		}
		break;
	case 0x05: // dec b z 1 h -
		{
			short answer = m_B - 1;
			m_F.z = ((answer & 0xFF) == 0);
			m_F.n = 1;
			m_F.h = ((answer & 0xF) == 0xF && m_B != 0);
			m_B = answer & 0xFF;
			m_cycles += 4;
		}
		break;
	case 0x06: // LD B,d8 - - - 
		{
			m_B = opcode[1];
			m_PC++;
			m_cycles += 8; 
		}
		break;
	case 0x07: // RLCA 0 0 0 c
		{
			short answer = m_A << 1;
			m_F.z = ((answer & 0xFF) == 0);
			m_F.n = 0;
			m_F.h = 0;
			m_F.c = (answer > 0xFF);
			m_A = answer & 0xFF;
			m_cycles += 4;
		}
		break;
	case 0x08: // LD (a16),sp - - - -
		{
			uint offset = opcode[1] << 8 | opcode[2];
			mem[offset] = (m_SP >> 8 ) & 0xFF;
			mem[offset + 1] = m_SP & 0xFF;
			m_PC += 2;
			m_cycles += 20;
		}
		break;
	case 0x09: // add HL, BC - 0 h c
		{
			uint answer = ((m_H << 8) | m_L) + ((m_B << 8) | m_C);
			ushort hc = answer & 0xFFFF;
			m_F.n = 0;
			m_F.c = (answer > 0xFFFF);
			m_F.h = (answer );
			m_cycles += 4;
		}
		break;

	}

	// increment opcode by one
	m_PC++;
}

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
