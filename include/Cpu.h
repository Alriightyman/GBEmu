#pragma once
#include "Memory.h"

// emulates the gameboy cpu.  Similar to a Z80 and 8080 processor
// See http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf for details

/*				GB CPU Speed	NOP Instruction
Machine Cycles		1.05MHz			1 cycle
Clock Cycles		4.19MHz			4 cycles
_____________________________________________________________________

  Registers
 -----------
|15..8 7...0|
|-----------|
|  A  |  F  |
|-----------|
|  B  |  C  |
|-----------|
|  D  |  E  |
|-----------|
|  H  |  L  |
|-----------|
|     SP    |
|-----------|
|     PC    |
 -----------
 
 Flag Registers
/---------------\
|7|6|5|4|3|2|1|0|
|---------------|
|Z|N|H|C|0|0|0|0|
\---------------/
Zero Flag (Z):
	This bit is set when the result of a math operation
	is zero or two values match when using the CP
	instruction.
Subtract Flag (N):
	This bit is set if a subtraction was performed in the
	last math instruction.
Half Carry Flag (H):
	This bit is set if a carry occurred from the lower
	nibble in the last math operation.
Carry Flag (C):
	This bit is set if a carry occurred from the last
	math operation or if register A is the smaller value
	when executing the CP instruction.

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
/*	struct Flags 
	{
		byte z:1;
		byte n:1;
		byte h:1;
		byte c:1;
		byte unused:4;
	};
*/
	typedef uint(Cpu::*opcode_func)(Memory&);
private:

#pragma region Member Variables

	struct Registers
	{
		union
		{
			struct
			{
				byte F;
				byte A;
			};
			ushort AF;
		};

		union
		{
			struct
			{
				byte C;
				byte B;
			};
			ushort BC;
		};

		union
		{
			struct
			{
				byte E;
				byte D;
			};
			ushort DE;
		};


		union
		{
			struct
			{
				byte L;
				byte H;
			};
			ushort HL;
		};


		ushort SP;
		ushort PC;
	};
	uint m_cycles;

	const opcode_func opcodes[255] =
	{
		&Cpu::NOP, &Cpu::LD_BC_nn, &Cpu::LD_addrBC_A, &Cpu::INC_BC, &Cpu::INC_B,&Cpu::DEC_B, &Cpu::LD_Bn, &Cpu::RLCA, &Cpu::LD_addrNN_SP, &Cpu::ADD_HLBC,
		&Cpu::LD_AaddrBC, &Cpu::DEC_BC,
		
	};

#pragma endregion

	Registers registers;
public:
	Cpu();
	bool Initialize();
	void Run(Memory& mem);

#pragma region Accessors/Mutators
	// Accessor/Mutators
	// Regsiter A
	byte GetRegA() const {return registers.A;}
	void SetRegA(byte value) { registers.A = value; }
	// Register F, Flag Register
	void ClearFlags() { registers.F = 0; } // m_Flags.c = m_Flags.h = m_Flags.n = m_Flags.z = m_Flags.unused = 0;

	bool GetZFlag() 
	{
		return (bool)(registers.F >> 8) & 0xFC;
	}
	//bool GetNFlag() { return m_Flags.n; }
	//bool GetHFlag() { return m_Flags.h; }
	//bool GetCFlag() { return m_Flags.c; }
	//void SetZFlag(bool bit) { m_Flags.z = bit; }
	//void SetNFlag(bool bit) { m_Flags.n = bit; }
	//void SetHFlag(bool bit) { m_Flags.h = bit; }
	//void SetCFlag(bool bit) { m_Flags.c = bit; }
	//// Reg B
	byte GetRegB() const {return registers.B;}
	void SetRegB(byte value) { registers.B = value; }
	// register C
	byte GetRegC() const {return registers.C;}
	void SetRegC(byte value) { registers.C = value; }
	// register BC
	short GetRegBC() const {return (registers.B << 8) | registers.C;}
	void SetRegBC(short value) { registers.B = (value >> 8) & 0xFF; registers.C = value & 0xFF; }
	// Register D
	byte GetRegD() const {return registers.D;}
	void SetRegD(byte value) { registers.D = value; }
	// register E
	byte GetRegE() const {return registers.E;}
	void SetRegE(byte value) { registers.E = value; }
	// register DE
	short GetRegDE() const {return (registers.D << 8) | registers.E;}
	void SetRegDE(short value) { registers.D = (value >> 8) & 0xFF; registers.E = value & 0xFF; }
	// Register H
	byte GetRegH() const {return registers.H;}
	void SetRegH(byte value) { registers.H = value; }
	// register L
	byte GetRegL() const {return registers.L;}
	void SetRegL(byte value) { registers.L = value; }
	// register HL
	short GetRegHL() const {return (registers.H << 8) | registers.L;}
	void SetRegHL(short value) { registers.H = (value >> 8) & 0xFF; registers.L = value & 0xFF; }
	// Register SP
	short GetStackPointer() const { return registers.SP; }
	void SetStackPointer(short value) { registers.SP = value; }
	// Register PC
	short GetProgramCounter()const { return registers.PC; }
	void SetProgramCounter(short value) { registers.PC = value; }
#pragma endregion
private:
//#ifdef FNCPTRS

	static int Load16BitImmediate(Memory mem, Registers* regs);
/* 
opcode 0xXX X bytes, X cycles
Descritpion: 
args: 
*/
#pragma region Commands
// all command return the number of cycles executed

	// opcode 0x00 1 byte, 4 cycles
	uint NOP(Memory& mem);

	/* opcode 0x01 3 bytes, 12 cycles
	 Descritpion: Put value nn into BC
	 args: nn = 16 bit immediate value */
	uint LD_BC_nn(Memory& mem);

	/* opcode 0x02 1 bytes, 8 cycles
	 Descritpion: Put A into (BC) */
	uint LD_addrBC_A(Memory& mem);

	/* opcode 0x03 1 bytes, 8 cycles
	 Descritpion: Increment register BC
	 Flags: NONE */
	uint INC_BC(Memory& mem);

	/* opcode 0x04 1 bytes, 4 cycles
	 Descritpion: Increment register B
	 Flags:
		Z - Set if result is zero.
		N - Reset.
		H - Set if carry from bit 3.
		C - Not affected */
	uint INC_B(Memory& mem);

	/*
	opcode 0x05 1 bytes, 4 cycles
	Descritpion: Decrement register B
	Flags:
		Z - Set if reselt is zero.
		N - Set.
		H - Set if no borrow from bit 4.
		C - Not affected.
	*/
	uint DEC_B(Memory& mem);

	/*
	opcode 0x06 2 bytes, 8 cycles
	Descritpion: Put value n into register B
	args: n = 8 bit immediate value
	*/
	uint LD_Bn(Memory& mem);

	/*
	opcode 0x07 1 bytes, 4 cycles
	Descritpion: Rotate A left. Old bit 7 to Carry flag.
	Flags:
		Z - Set if result is zero.
		N - Reset.
		H - Reset.
		C - Contains old bit 7 data.
	*/
	uint RLCA(Memory& mem);

	/*
	opcode 0x08 3 bytes, 20 cycles
	Descritpion: Put Stack Pointer (SP) at address nn
	args: nn = two byte immediate address.
	*/
	uint LD_addrNN_SP(Memory& mem);

	/*
	opcode 0x09 1 bytes, 8 cycles
	Descritpion: Add BC to HL.
	Flags:
		Z - Not affected.
		N - Reset.
		H - Set if carry from bit 11.
		C - Set if carry from bit 15.
	*/
	uint ADD_HLBC(Memory& mem);

	/*
	opcode 0x0A 1 bytes, 8 cycles
	Descritpion: put value of (BC) in A
	args: (BC) is address 
	*/
	uint LD_AaddrBC(Memory& mem);

	/*
	opcode 0x0B 1 bytes, 8 cycles
	Descritpion: Decrement BC
	Flags: NONE
	*/
	uint DEC_BC(Memory& mem);


#pragma endregion

//#endif
};

