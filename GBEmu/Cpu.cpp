#include "Cpu.h"



Cpu::Cpu() 
	: m_cycles(0)
{
	registers.A = 0x0;
	registers.B = 0;
	registers.C = 0x13;
	registers.D = 0;
	registers.E = 0xD8; 
	registers.H = 0x1; 
	registers.L = 0x4D;
	registers.SP = 0xFFFE;
	registers.PC = 0x100;
}

bool Cpu::Initialize()
{


	return true;
}


void Cpu::Run(Memory& mem)
{
	byte* opcode = &mem[registers.PC];
	
	opcode_func method = opcodes[*opcode];
	uint cycles = (this->*method)(mem);

	m_cycles += cycles;	
}

#pragma region Opcode Functions

#pragma endregion

#pragma region Helper functions
 // 16-bit Load command helper
int Cpu::Load16BitImmediate(Memory mem, Registers* regs)
{
	ushort nn = mem[++regs->PC] << 8 | mem[++regs->PC];
	regs->PC++;

	return nn;
}


#pragma endregion

uint Cpu::NOP(Memory & mem)
{
	this->registers.PC++;
	return 4;
}

uint Cpu::LD_BC_nn(Memory & mem)
{
	registers.BC = Load16BitImmediate(mem, &this->registers);
	return 12;
}

uint Cpu::LD_addrBC_A(Memory & mem)
{
	registers.BC = registers.A;
	registers.PC++;

	return 8;
}

uint Cpu::INC_BC(Memory & mem)
{
	registers.BC++;
	return 8;
}

uint Cpu::INC_B(Memory & mem)
{
	registers.B++;
	registers.PC++;
	byte z = (registers.B == 0);
	byte n = 0; 
	byte h = 0; // todo
	byte c = 0; // todo


	return 4;
}
