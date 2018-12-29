#pragma once
/*
GMB 8bit-Arithmetic/logical Commands
	add  A,r         8x         4 z0hc A=A+r
	add  A,n         C6 nn      8 z0hc A=A+n
	add  A,(HL)      86         8 z0hc A=A+(HL)
	adc  A,r         8x         4 z0hc A=A+r+cy
	adc  A,n         CE nn      8 z0hc A=A+n+cy
	adc  A,(HL)      8E         8 z0hc A=A+(HL)+cy
	sub  r           9x         4 z1hc A=A-r
	sub  n           D6 nn      8 z1hc A=A-n
	sub  (HL)        96         8 z1hc A=A-(HL)
	sbc  A,r         9x         4 z1hc A=A-r-cy
	sbc  A,n         DE nn      8 z1hc A=A-n-cy
	sbc  A,(HL)      9E         8 z1hc A=A-(HL)-cy
	and  r           Ax         4 z010 A=A & r
	and  n           E6 nn      8 z010 A=A & n
	and  (HL)        A6         8 z010 A=A & (HL)
	xor  r           Ax         4 z000
	xor  n           EE nn      8 z000
	xor  (HL)        AE         8 z000
	or   r           Bx         4 z000 A=A | r
	or   n           F6 nn      8 z000 A=A | n
	or   (HL)        B6         8 z000 A=A | (HL)
	cp   r           Bx         4 z1hc compare A-r
	cp   n           FE nn      8 z1hc compare A-n
	cp   (HL)        BE         8 z1hc compare A-(HL)
	cpl              2F         4 -11- A = A xor FF

GMB 16bit-Arithmetic/logical Commands
	add  HL,rr     x9           8 -0hc HL = HL+rr     ;rr may be BC,DE,HL,SP
	add  SP,dd     E8          16 00hc SP = SP +/- dd ;dd is 8bit signed number
*/
#include "TypesDef.h"

namespace Gameboy
{
	class Register;

	class ALU
	{
	private:
		// keep a copy of the AF Register for flag purposes
		Register* af;

	public:
		ALU();
		~ALU();
		void Initialize(Register* AF);

		/* ADD commands 
			add  A,r         8x         4 z0hc A=A+r
			add  A,n         C6 nn      8 z0hc A=A+n
			add  A,(HL)      86         8 z0hc A=A+(HL)
			add  HL,rr     x9           8 -0hc HL = HL+rr     ;rr may be BC,DE,HL,SP
			add  SP,dd     E8          16 00hc SP = SP +/- dd ;dd is 8bit signed number
		*/
		// add 8bit value to 8bit register
		void Add(u8 n);
		// add 16bit value to 16bit register 
		void Add(u16& hl, u16 n);
		// add to stack pointer
		void Add(u16& sp, s8 n);

		/* ADC command
			adc  A,r         8x         4 z0hc A=A+r+cy
			adc  A,n         CE nn      8 z0hc A=A+n+cy
			adc  A,(HL)      8E         8 z0hc A=A+(HL)+cy
		*/
		void Adc(u8 n);

		/* SUB commands 
			sub  r           9x         4 z1hc A=A-r
			sub  n           D6 nn      8 z1hc A=A-n
			sub  (HL)        96         8 z1hc A=A-(HL)
		*/
		void Sub(u8 n);

		/* SBC Commands
			sbc  A,r         9x         4 z1hc A=A-r-cy
			sbc  A,n         DE nn      8 z1hc A=A-n-cy
			sbc  A,(HL)      9E         8 z1hc A=A-(HL)-cy
		*/
		void Sbc(u8& a, u8 n);

		/* AND commands
			and  r           Ax         4 z010 A=A & r
			and  n           E6 nn      8 z010 A=A & n
			and  (HL)        A6         8 z010 A=A & (HL)
		*/
		void And(u8& a, u8 n);

		/* XOR commands
			xor  r           Ax         4 z000
			xor  n           EE nn      8 z000
			xor  (HL)        AE         8 z000
		*/
		void XOR(u8& a, u8 n);

		/* OR commands
			or   r           Bx         4 z000 A=A | r
			or   n           F6 nn      8 z000 A=A | n
			or   (HL)        B6         8 z000 A=A | (HL)
		*/
		void OR(u8& a, u8 n);

		/* CP commands
			cp   r           Bx         4 z1hc compare A-r
			cp   n           FE nn      8 z1hc compare A-n
			cp   (HL)        BE         8 z1hc compare A-(HL)
		*/
		void CP(u8& a, u8 n);

	};
}
