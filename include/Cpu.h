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

	const opcode_func opcodes[256] =
	{
		// 0xN0,		0xN1,           0xN2,				0xN3,			0xN4,			0xN5,			0xN6,			0xN7,			0xN8,               0xN9,           0xNA,				0xNB,			0xNC,			0xND,			0xNE,				0xNF
		&Cpu::NOP,		&Cpu::LD_BC_nn, &Cpu::LD_BCA,		&Cpu::INC_BC,	&Cpu::INC_B,	&Cpu::DEC_B,	&Cpu::LD_Bn,	&Cpu::RLCA,		&Cpu::LD_addrNN_SP, &Cpu::ADD_HLBC, &Cpu::LD_ABC,		&Cpu::DEC_BC,	&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_Cn,		&Cpu::NOP,		// 0x00-0x0F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_DEA,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_Dn,	&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::LD_ADE,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_En,		&Cpu::NOP,		// 0x10-0x1F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_Hn,	&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_Ln,		&Cpu::NOP,		// 0x20-0x2F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_ANumber,	&Cpu::NOP,		// 0x30-0x3F
		&Cpu::LD_BB,	&Cpu::LD_BC,	&Cpu::LD_BD,		&Cpu::LD_BE,	&Cpu::LD_BH,	&Cpu::LD_BL,	&Cpu::LD_BHL,	&Cpu::LD_BA,	&Cpu::LD_CB,		&Cpu::LD_CC,	&Cpu::LD_CD,		&Cpu::LD_CE,	&Cpu::LD_CH,	&Cpu::LD_CL,	&Cpu::LD_CHL,		&Cpu::LD_CA,	// 0x40-0x4F
		&Cpu::LD_DB,	&Cpu::LD_DC,	&Cpu::LD_DD,		&Cpu::LD_DE,	&Cpu::LD_DH,	&Cpu::LD_DL,	&Cpu::LD_DHL,	&Cpu::LD_DA,	&Cpu::LD_EB,		&Cpu::LD_EC,	&Cpu::LD_ED,		&Cpu::LD_EE,	&Cpu::LD_EH,	&Cpu::LD_EL,	&Cpu::LD_EHL,		&Cpu::LD_EA,	// 0x50-0x5F
		&Cpu::LD_HB,	&Cpu::LD_HC,	&Cpu::LD_HD,		&Cpu::LD_HE,	&Cpu::LD_HH,	&Cpu::LD_HL,	&Cpu::LD_HHL,	&Cpu::LD_HA,	&Cpu::LD_LB,		&Cpu::LD_LC,	&Cpu::LD_LD,		&Cpu::LD_LE,	&Cpu::LD_LH,	&Cpu::LD_LL,	&Cpu::LD_LHL,		&Cpu::LD_LA,	// 0x60-0x6F
		&Cpu::LD_HLB,	&Cpu::LD_HLC,	&Cpu::LD_HLD,		&Cpu::LD_HLE,	&Cpu::LD_HLH,	&Cpu::LD_HLL,	&Cpu::LD_HLn,	&Cpu::LD_HLA,	&Cpu::LD_AB,		&Cpu::LD_AC,	&Cpu::LD_AD,		&Cpu::LD_AE,	&Cpu::LD_AH,	&Cpu::LD_AL,	&Cpu::LD_AHL,		&Cpu::LD_AA,	// 0x70-0x7F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0x80-0x8F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0x90-0x9F
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0xA0-0xAF
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0xB0-0xBF
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0xC0-0xCF
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0xD0-0xDF
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_AdrrC_A,	&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::LD_nnA,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		// 0xE0-0xEF
		&Cpu::NOP,		&Cpu::NOP,		&Cpu::LD_A_AdrrC,	&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP,		&Cpu::LD_Ann,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,		&Cpu::NOP,			&Cpu::NOP		// 0xF0-0xFF
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

	static int Load16BitImmediate(Memory mem, Registers* regs);
/* 
opcode 0xXX X bytes, X cycles
Descritpion: 
args: 
*/
#pragma region Commands

	#pragma region 8 - Bit Loads
	/*
	1. LD nn,n
		Description:
		 Put value nn into n.
		Use with:
		 nn = B,C,D,E,H,L,BC,DE,HL,SP
		 n = 8 bit immediate value

		 2 bytes, 8 cycles
	*/	
	// opcode 0x06 
	uint LD_Bn(Memory& mem);
	// opcode 0x0E 
	uint LD_Cn(Memory& mem);
	// opcode 0x16 
	uint LD_Dn(Memory& mem);
	// opcode 0x1E 
	uint LD_En(Memory& mem);
	// opcode 0x26 
	uint LD_Hn(Memory& mem);
	// opcode 0x2E 
	uint LD_Ln(Memory& mem);
	/*
	2. LD r1,r2
		Description:
		 Put value r2 into r1.
		Use with:
		 r1,r2 = A,B,C,D,E,H,L,(HL)
	*/
	// opcode 7F; 4 cycles
	uint LD_AA(Memory& mem);
	// opcode 78; 4 cycles
	uint LD_AB(Memory& mem);
	// opcode 79; 4 cycles
	uint LD_AC(Memory& mem);
	// opcode 7A; 4 cycles
	uint LD_AD(Memory& mem);
	// opcode 7B; 4 cycles
	uint LD_AE(Memory& mem);
	// opcode 7C; 4 cycles
	uint LD_AH(Memory& mem);
	// opcode 7D; 4 cycles
	uint LD_AL(Memory& mem);
	// opcode 7E; 8 cycles
	uint LD_AHL(Memory& mem);

	// opcode 40; 4 cycles
	uint LD_BB(Memory& mem);
	// opcode 41; 4 cycles
	uint LD_BC(Memory& mem);
	// opcode 42; 4 cycles
	uint LD_BD(Memory& mem);
	// opcode 43; 4 cycles
	uint LD_BE(Memory& mem);
	// opcode 44; 4 cycles
	uint LD_BH(Memory& mem);
	// opcode 45; 4 cycles
	uint LD_BL(Memory& mem);
	// opcode 46; 8 cycles
	uint LD_BHL(Memory& mem);

	// opcode 48; 4 cycles
	uint LD_CB(Memory& mem);
	// opcode 49; 4 cycles
	uint LD_CC(Memory& mem);
	// opcode 4A; 4 cycles
	uint LD_CD(Memory& mem);
	// opcode 4B; 4 cycles
	uint LD_CE(Memory& mem);
	// opcode 4C; 4 cycles
	uint LD_CH(Memory& mem);
	// opcode 4D; 4 cycles
	uint LD_CL(Memory& mem);
	// opcode 4E; 8 cycles
	uint LD_CHL(Memory& mem);

	// opcode 50; 4 cycles
	uint LD_DB(Memory& mem);
	// opcode 51; 4 cycles
	uint LD_DC(Memory& mem);
	// opcode 52; 4 cycles
	uint LD_DD(Memory& mem);
	// opcode 53; 4 cycles
	uint LD_DE(Memory& mem);
	// opcode 54; 4 cycles
	uint LD_DH(Memory& mem);
	// opcode 55; 4 cycles
	uint LD_DL(Memory& mem);
	// opcode 56; 8 cycles
	uint LD_DHL(Memory& mem);

	// opcode 58; 4 cycles
	uint LD_EB(Memory& mem);
	// opcode 59; 4 cycles
	uint LD_EC(Memory& mem);
	// opcode 5A; 4 cycles
	uint LD_ED(Memory& mem);
	// opcode 5B; 4 cycles
	uint LD_EE(Memory& mem);
	// opcode 5C; 4 cycles
	uint LD_EH(Memory& mem);
	// opcode 5D; 4 cycles
	uint LD_EL(Memory& mem);
	// opcode 5E; 8 cycles
	uint LD_EHL(Memory& mem);

	// opcode 60; 4 cycles
	uint LD_HB(Memory& mem);
	// opcode 61; 4 cycles
	uint LD_HC(Memory& mem);
	// opcode 62; 4 cycles
	uint LD_HD(Memory& mem);
	// opcode 63; 4 cycles
	uint LD_HE(Memory& mem);
	// opcode 64; 4 cycles
	uint LD_HH(Memory& mem);
	// opcode 65; 4 cycles
	uint LD_HL(Memory& mem);
	// opcode 66; 8 cycles
	uint LD_HHL(Memory& mem);

	// opcode 68; 4 cycles
	uint LD_LB(Memory& mem);
	// opcode 69; 4 cycles
	uint LD_LC(Memory& mem);
	// opcode 6A; 4 cycles
	uint LD_LD(Memory& mem);
	// opcode 6B; 4 cycles
	uint LD_LE(Memory& mem);
	// opcode 6C; 4 cycles
	uint LD_LH(Memory& mem);
	// opcode 6D; 4 cycles
	uint LD_LL(Memory& mem);
	// opcode 6E; 8 cycles
	uint LD_LHL(Memory& mem);

	// opcode 70;  cycles
	uint LD_HLB(Memory& mem);
	// opcode 71; 8 cycles
	uint LD_HLC(Memory& mem);
	// opcode 72; 8 cycles
	uint LD_HLD(Memory& mem);
	// opcode 73; 8 cycles
	uint LD_HLE(Memory& mem);
	// opcode 74; 8 cycles
	uint LD_HLH(Memory& mem);
	// opcode 75; 8 cycles
	uint LD_HLL(Memory& mem);
	// opcode 36; 12 cycles
	uint LD_HLn(Memory& mem);

	/*
	3. LD A,n
		Description:
		 Put value n into A.
		Use with:
		 n = A,B,C,D,E,H,L,(BC),(DE),(HL),(nn),#
		 nn = two byte immediate value. (LS byte first.)
	*/
	// opcode 0A; 8 cycles
	uint LD_ABC(Memory& mem);
	// opcode 1A; 8 cycles
	uint LD_ADE(Memory& mem);
	// opcode FA; 16 cycles
	uint LD_Ann(Memory& mem);
	// opcode 3E; 8 cycles
	uint LD_ANumber(Memory& mem);

	/*
	4. LD n,A
		Description:
		 Put value A into n.
		Use with:
		 n = A,B,C,D,E,H,L,(BC),(DE),(HL),(nn)
		 nn = two byte immediate value. (LS byte first.)
	*/
	// opcode 47; 4 cycles
	uint LD_BA(Memory& mem);
	// opcode 4F; 4 cycles
	uint LD_CA(Memory& mem);
	// opcode 57; 4 cycles
	uint LD_DA(Memory& mem);
	// opcode 5F; 4 cycles
	uint LD_EA(Memory& mem);
	// opcode 67; 4 cycles
	uint LD_HA(Memory& mem);
	// opcode 6F; 4 cycles
	uint LD_LA(Memory& mem);
	// opcode 2; 8 cycles
	uint LD_BCA(Memory& mem);
	// opcode 12; 8 cycles
	uint LD_DEA(Memory& mem);
	// opcode 77; 8 cycles
	uint LD_HLA(Memory& mem);
	// opcode EA; 16 cycles
	uint LD_nnA(Memory& mem);

	/*
	5. LD A,(C)
		Description:
		 Put value at address $FF00 + register C into A.
		 Same as: LD A,($FF00+C)
	*/
	// opcode F2; 8 cycles
	uint LD_A_AdrrC(Memory& mem);

	/*
	6. LD (C),A
		Description:
		 Put A into address $FF00 + register C.
	*/
	// opcode E2; 8 cycles
	uint LD_AdrrC_A(Memory& mem);

	/*
	7. LD A,(HLD)
		Description: Same as: LDD A,(HL)
	8. LD A,(HL-)
		Description: Same as: LDD A,(HL)
	9. LDD A,(HL)
		Description:
		 Put value at address HL into A. Decrement HL.
		 Same as: LD A,(HL) - DEC HL
	*/
	// 
	#pragma endregion


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

