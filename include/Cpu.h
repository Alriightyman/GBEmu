#pragma once
#include "Memory.h"
// emulates the gameboy cpu.  Similar to a Z80 and 8080 processor
/*				GB CPU Speed	NOP Instruction
Machine Cycles		1.05MHz			1 cycle
Clock Cycles		4.19MHz			4 cycles
*/
//// forward declaration
//class Memory;
//typedef char byte;
typedef unsigned int uint;
typedef unsigned short ushort;

// Flag bits
#define ZFlag 7
#define NFlag 6
#define HFlag 5
#define CFlag 4


class Cpu
{
private:
	struct FReg 
	{
		byte z:1;
		byte n:1;
		byte h:1;
		byte c:1;
		byte unused:4;
	};

private:
#pragma region Member Variables
	byte m_A;
	byte m_B,m_C;
	byte m_D,m_E;
	byte m_H,m_L;
	ushort m_SP; 
	ushort m_PC;
	FReg m_F;
	uint m_cycles;

#pragma endregion


public:
	Cpu();
	bool Initialize();
	void Run(Memory& mem);

#pragma region Accessors/Mutators
	// Accessor/Mutators
	// Regsiter A
	byte GetRegA() const {return m_A;}
	void SetRegA(byte value) { m_A = value; }
	// Register F, Flag Register
	void ClearFlags() { m_F.c = m_F.h = m_F.n = m_F.z = m_F.unused = 0; }
	bool GetZFlag() { return m_F.z; }
	bool GetNFlag() { return m_F.n; }
	bool GetHFlag() { return m_F.h; }
	bool GetCFlag() { return m_F.c; }
	void SetZFlag(bool bit) { m_F.z = bit; }
	void SetNFlag(bool bit) { m_F.n = bit; }
	void SetHFlag(bool bit) { m_F.h = bit; }
	void SetCFlag(bool bit) { m_F.c = bit; }
	// Reg B
	byte GetRegB() const {return m_B;}
	void SetRegB(byte value) { m_B = value; }
	// register C
	byte GetRegC() const {return m_C;}
	void SetRegC(byte value) { m_C = value; }
	// register BC
	short GetRegBC() const {return (m_B << 8) | m_C;}
	void SetRegBC(short value) { m_B = (value >> 8) & 0xFF; m_C = value & 0xFF; }
	// Register D
	byte GetRegD() const {return m_D;}
	void SetRegD(byte value) { m_D = value; }
	// register E
	byte GetRegE() const {return m_E;}
	void SetRegE(byte value) { m_E = value; }
	// register DE
	short GetRegDE() const {return (m_D << 8) | m_E;}
	void SetRegDE(short value) { m_D = (value >> 8) & 0xFF; m_E = value & 0xFF; }
	// Register H
	byte GetRegH() const {return m_H;}
	void SetRegH(byte value) { m_H = value; }
	// register L
	byte GetRegL() const {return m_L;}
	void SetRegL(byte value) { m_L = value; }
	// register HL
	short GetRegHL() const {return (m_H << 8) | m_L;}
	void SetRegHL(short value) { m_H = (value >> 8) & 0xFF; m_L = value & 0xFF; }
	// Register SP
	short GetStackPointer() const { return m_SP; }
	void SetStackPointer(short value) { m_SP = value; }
	// Register PC
	short GetProgramCounter()const { return m_PC; }
	void SetProgramCounter(short value) { m_PC = value; }
#pragma endregion
private:
#ifdef FNCPTRS
#pragma region Commands
// all command return the number of cycles executed
// 1 byte, 4 cycles					// 00
uint NOP(Memory& mem);
// 3 bytes, 12 cycles				// 01
uint LD_BCd16(Memory& mem);	
// 1 byte, 8 cycles					// 02
uint LD_addrBC_A(Memory& mem);
// 1 byte, 8 cycles					// 03
uint INC_BC(Memory& mem);
// 1 byte, 4 cycles, Z 0 H -		// 04
uint INC_B(Memory& mem);
// 1 byte, 4 cycles, Z 1 H -		// 05
uint DEC_B(Memory& mem);
// 2 bytes, 8 cycles				// 06
uint LD_Bd8(Memory& mem);
// 1 byte, 4 cycles, 0 0 0 C		// 07
uint RLCA(Memory& mem);

#pragma endregion
#endif
};

