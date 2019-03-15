#pragma once
#include "Register.h"
#include "ALU.h"
#include "MMU.h"
#include <string>

namespace Gameboy
{
	class CPU
	{

	#pragma region Opcode function tables
		typedef void(CPU::*OpcodeFunction)();
		const OpcodeFunction Opcodes[256] =
		{
			&CPU::Opcode00,&CPU::Opcode01,&CPU::Opcode02,&CPU::Opcode03,&CPU::Opcode04,&CPU::Opcode05,&CPU::Opcode06,&CPU::Opcode07,&CPU::Opcode08,&CPU::Opcode09,&CPU::Opcode0A,&CPU::Opcode0B,&CPU::Opcode0C,&CPU::Opcode0D,&CPU::Opcode0E,&CPU::Opcode0F,
			&CPU::Opcode10,&CPU::Opcode11,&CPU::Opcode12,&CPU::Opcode13,&CPU::Opcode14,&CPU::Opcode15,&CPU::Opcode16,&CPU::Opcode17,&CPU::Opcode18,&CPU::Opcode19,&CPU::Opcode1A,&CPU::Opcode1B,&CPU::Opcode1C,&CPU::Opcode1D,&CPU::Opcode1E,&CPU::Opcode1F,
			&CPU::Opcode20,&CPU::Opcode21,&CPU::Opcode22,&CPU::Opcode23,&CPU::Opcode24,&CPU::Opcode25,&CPU::Opcode26,&CPU::Opcode27,&CPU::Opcode28,&CPU::Opcode29,&CPU::Opcode2A,&CPU::Opcode2B,&CPU::Opcode2C,&CPU::Opcode2D,&CPU::Opcode2E,&CPU::Opcode2F,
			&CPU::Opcode30,&CPU::Opcode31,&CPU::Opcode32,&CPU::Opcode33,&CPU::Opcode34,&CPU::Opcode35,&CPU::Opcode36,&CPU::Opcode37,&CPU::Opcode38,&CPU::Opcode39,&CPU::Opcode3A,&CPU::Opcode3B,&CPU::Opcode3C,&CPU::Opcode3D,&CPU::Opcode3E,&CPU::Opcode3F,
			&CPU::Opcode40,&CPU::Opcode41,&CPU::Opcode42,&CPU::Opcode43,&CPU::Opcode44,&CPU::Opcode45,&CPU::Opcode46,&CPU::Opcode47,&CPU::Opcode48,&CPU::Opcode49,&CPU::Opcode4A,&CPU::Opcode4B,&CPU::Opcode4C,&CPU::Opcode4D,&CPU::Opcode4E,&CPU::Opcode4F,
			&CPU::Opcode50,&CPU::Opcode51,&CPU::Opcode52,&CPU::Opcode53,&CPU::Opcode54,&CPU::Opcode55,&CPU::Opcode56,&CPU::Opcode57,&CPU::Opcode58,&CPU::Opcode59,&CPU::Opcode5A,&CPU::Opcode5B,&CPU::Opcode5C,&CPU::Opcode5D,&CPU::Opcode5E,&CPU::Opcode5F,
			&CPU::Opcode60,&CPU::Opcode61,&CPU::Opcode62,&CPU::Opcode63,&CPU::Opcode64,&CPU::Opcode65,&CPU::Opcode66,&CPU::Opcode67,&CPU::Opcode68,&CPU::Opcode69,&CPU::Opcode6A,&CPU::Opcode6B,&CPU::Opcode6C,&CPU::Opcode6D,&CPU::Opcode6E,&CPU::Opcode6F,
			&CPU::Opcode70,&CPU::Opcode71,&CPU::Opcode72,&CPU::Opcode73,&CPU::Opcode74,&CPU::Opcode75,&CPU::Opcode76,&CPU::Opcode77,&CPU::Opcode78,&CPU::Opcode79,&CPU::Opcode7A,&CPU::Opcode7B,&CPU::Opcode7C,&CPU::Opcode7D,&CPU::Opcode7E,&CPU::Opcode7F,
			&CPU::Opcode80,&CPU::Opcode81,&CPU::Opcode82,&CPU::Opcode83,&CPU::Opcode84,&CPU::Opcode85,&CPU::Opcode86,&CPU::Opcode87,&CPU::Opcode88,&CPU::Opcode89,&CPU::Opcode8A,&CPU::Opcode8B,&CPU::Opcode8C,&CPU::Opcode8D,&CPU::Opcode8E,&CPU::Opcode8F,
			&CPU::Opcode90,&CPU::Opcode91,&CPU::Opcode92,&CPU::Opcode93,&CPU::Opcode94,&CPU::Opcode95,&CPU::Opcode96,&CPU::Opcode97,&CPU::Opcode98,&CPU::Opcode99,&CPU::Opcode9A,&CPU::Opcode9B,&CPU::Opcode9C,&CPU::Opcode9D,&CPU::Opcode9E,&CPU::Opcode9F,
			&CPU::OpcodeA0,&CPU::OpcodeA1,&CPU::OpcodeA2,&CPU::OpcodeA3,&CPU::OpcodeA4,&CPU::OpcodeA5,&CPU::OpcodeA6,&CPU::OpcodeA7,&CPU::OpcodeA8,&CPU::OpcodeA9,&CPU::OpcodeAA,&CPU::OpcodeAB,&CPU::OpcodeAC,&CPU::OpcodeAD,&CPU::OpcodeAE,&CPU::OpcodeAF,
			&CPU::OpcodeB0,&CPU::OpcodeB1,&CPU::OpcodeB2,&CPU::OpcodeB3,&CPU::OpcodeB4,&CPU::OpcodeB5,&CPU::OpcodeB6,&CPU::OpcodeB7,&CPU::OpcodeB8,&CPU::OpcodeB9,&CPU::OpcodeBA,&CPU::OpcodeBB,&CPU::OpcodeBC,&CPU::OpcodeBD,&CPU::OpcodeBE,&CPU::OpcodeBF,
			&CPU::OpcodeC0,&CPU::OpcodeC1,&CPU::OpcodeC2,&CPU::OpcodeC3,&CPU::OpcodeC4,&CPU::OpcodeC5,&CPU::OpcodeC6,&CPU::OpcodeC7,&CPU::OpcodeC8,&CPU::OpcodeC9,&CPU::OpcodeCA,&CPU::OpcodeCB,&CPU::OpcodeCC,&CPU::OpcodeCD,&CPU::OpcodeCE,&CPU::OpcodeCF,
			&CPU::OpcodeD0,&CPU::OpcodeD1,&CPU::OpcodeD2,&CPU::OpcodeD3,&CPU::OpcodeD4,&CPU::OpcodeD5,&CPU::OpcodeD6,&CPU::OpcodeD7,&CPU::OpcodeD8,&CPU::OpcodeD9,&CPU::OpcodeDA,&CPU::OpcodeDB,&CPU::OpcodeDC,&CPU::OpcodeDD,&CPU::OpcodeDE,&CPU::OpcodeDF,
			&CPU::OpcodeE0,&CPU::OpcodeE1,&CPU::OpcodeE2,&CPU::OpcodeE3,&CPU::OpcodeE4,&CPU::OpcodeE5,&CPU::OpcodeE6,&CPU::OpcodeE7,&CPU::OpcodeE8,&CPU::OpcodeE9,&CPU::OpcodeEA,&CPU::OpcodeEB,&CPU::OpcodeEC,&CPU::OpcodeED,&CPU::OpcodeEE,&CPU::OpcodeEF,
			&CPU::OpcodeF0,&CPU::OpcodeF1,&CPU::OpcodeF2,&CPU::OpcodeF3,&CPU::OpcodeF4,&CPU::OpcodeF5,&CPU::OpcodeF6,&CPU::OpcodeF7,&CPU::OpcodeF8,&CPU::OpcodeF9,&CPU::OpcodeFA,&CPU::OpcodeFB,&CPU::OpcodeFC,&CPU::OpcodeFD,&CPU::OpcodeFE,&CPU::OpcodeFF
		};

		const OpcodeFunction OpcodeCBs[256] =
		{
			&CPU::OpcodeCB_00,&CPU::OpcodeCB_01,&CPU::OpcodeCB_02,&CPU::OpcodeCB_03,&CPU::OpcodeCB_04,&CPU::OpcodeCB_05,&CPU::OpcodeCB_06,&CPU::OpcodeCB_07,&CPU::OpcodeCB_08,&CPU::OpcodeCB_09,&CPU::OpcodeCB_0A,&CPU::OpcodeCB_0B,&CPU::OpcodeCB_0C,&CPU::OpcodeCB_0D,&CPU::OpcodeCB_0E,&CPU::OpcodeCB_0F,
			&CPU::OpcodeCB_10,&CPU::OpcodeCB_11,&CPU::OpcodeCB_12,&CPU::OpcodeCB_13,&CPU::OpcodeCB_14,&CPU::OpcodeCB_15,&CPU::OpcodeCB_16,&CPU::OpcodeCB_17,&CPU::OpcodeCB_18,&CPU::OpcodeCB_19,&CPU::OpcodeCB_1A,&CPU::OpcodeCB_1B,&CPU::OpcodeCB_1C,&CPU::OpcodeCB_1D,&CPU::OpcodeCB_1E,&CPU::OpcodeCB_1F,
			&CPU::OpcodeCB_20,&CPU::OpcodeCB_21,&CPU::OpcodeCB_22,&CPU::OpcodeCB_23,&CPU::OpcodeCB_24,&CPU::OpcodeCB_25,&CPU::OpcodeCB_26,&CPU::OpcodeCB_27,&CPU::OpcodeCB_28,&CPU::OpcodeCB_29,&CPU::OpcodeCB_2A,&CPU::OpcodeCB_2B,&CPU::OpcodeCB_2C,&CPU::OpcodeCB_2D,&CPU::OpcodeCB_2E,&CPU::OpcodeCB_2F,
			&CPU::OpcodeCB_30,&CPU::OpcodeCB_31,&CPU::OpcodeCB_32,&CPU::OpcodeCB_33,&CPU::OpcodeCB_34,&CPU::OpcodeCB_35,&CPU::OpcodeCB_36,&CPU::OpcodeCB_37,&CPU::OpcodeCB_38,&CPU::OpcodeCB_39,&CPU::OpcodeCB_3A,&CPU::OpcodeCB_3B,&CPU::OpcodeCB_3C,&CPU::OpcodeCB_3D,&CPU::OpcodeCB_3E,&CPU::OpcodeCB_3F,
			&CPU::OpcodeCB_40,&CPU::OpcodeCB_41,&CPU::OpcodeCB_42,&CPU::OpcodeCB_43,&CPU::OpcodeCB_44,&CPU::OpcodeCB_45,&CPU::OpcodeCB_46,&CPU::OpcodeCB_47,&CPU::OpcodeCB_48,&CPU::OpcodeCB_49,&CPU::OpcodeCB_4A,&CPU::OpcodeCB_4B,&CPU::OpcodeCB_4C,&CPU::OpcodeCB_4D,&CPU::OpcodeCB_4E,&CPU::OpcodeCB_4F,
			&CPU::OpcodeCB_50,&CPU::OpcodeCB_51,&CPU::OpcodeCB_52,&CPU::OpcodeCB_53,&CPU::OpcodeCB_54,&CPU::OpcodeCB_55,&CPU::OpcodeCB_56,&CPU::OpcodeCB_57,&CPU::OpcodeCB_58,&CPU::OpcodeCB_59,&CPU::OpcodeCB_5A,&CPU::OpcodeCB_5B,&CPU::OpcodeCB_5C,&CPU::OpcodeCB_5D,&CPU::OpcodeCB_5E,&CPU::OpcodeCB_5F,
			&CPU::OpcodeCB_60,&CPU::OpcodeCB_61,&CPU::OpcodeCB_62,&CPU::OpcodeCB_63,&CPU::OpcodeCB_64,&CPU::OpcodeCB_65,&CPU::OpcodeCB_66,&CPU::OpcodeCB_67,&CPU::OpcodeCB_68,&CPU::OpcodeCB_69,&CPU::OpcodeCB_6A,&CPU::OpcodeCB_6B,&CPU::OpcodeCB_6C,&CPU::OpcodeCB_6D,&CPU::OpcodeCB_6E,&CPU::OpcodeCB_6F,
			&CPU::OpcodeCB_70,&CPU::OpcodeCB_71,&CPU::OpcodeCB_72,&CPU::OpcodeCB_73,&CPU::OpcodeCB_74,&CPU::OpcodeCB_75,&CPU::OpcodeCB_76,&CPU::OpcodeCB_77,&CPU::OpcodeCB_78,&CPU::OpcodeCB_79,&CPU::OpcodeCB_7A,&CPU::OpcodeCB_7B,&CPU::OpcodeCB_7C,&CPU::OpcodeCB_7D,&CPU::OpcodeCB_7E,&CPU::OpcodeCB_7F,
			&CPU::OpcodeCB_80,&CPU::OpcodeCB_81,&CPU::OpcodeCB_82,&CPU::OpcodeCB_83,&CPU::OpcodeCB_84,&CPU::OpcodeCB_85,&CPU::OpcodeCB_86,&CPU::OpcodeCB_87,&CPU::OpcodeCB_88,&CPU::OpcodeCB_89,&CPU::OpcodeCB_8A,&CPU::OpcodeCB_8B,&CPU::OpcodeCB_8C,&CPU::OpcodeCB_8D,&CPU::OpcodeCB_8E,&CPU::OpcodeCB_8F,
			&CPU::OpcodeCB_90,&CPU::OpcodeCB_91,&CPU::OpcodeCB_92,&CPU::OpcodeCB_93,&CPU::OpcodeCB_94,&CPU::OpcodeCB_95,&CPU::OpcodeCB_96,&CPU::OpcodeCB_97,&CPU::OpcodeCB_98,&CPU::OpcodeCB_99,&CPU::OpcodeCB_9A,&CPU::OpcodeCB_9B,&CPU::OpcodeCB_9C,&CPU::OpcodeCB_9D,&CPU::OpcodeCB_9E,&CPU::OpcodeCB_9F,
			&CPU::OpcodeCB_A0,&CPU::OpcodeCB_A1,&CPU::OpcodeCB_A2,&CPU::OpcodeCB_A3,&CPU::OpcodeCB_A4,&CPU::OpcodeCB_A5,&CPU::OpcodeCB_A6,&CPU::OpcodeCB_A7,&CPU::OpcodeCB_A8,&CPU::OpcodeCB_A9,&CPU::OpcodeCB_AA,&CPU::OpcodeCB_AB,&CPU::OpcodeCB_AC,&CPU::OpcodeCB_AD,&CPU::OpcodeCB_AE,&CPU::OpcodeCB_AF,
			&CPU::OpcodeCB_B0,&CPU::OpcodeCB_B1,&CPU::OpcodeCB_B2,&CPU::OpcodeCB_B3,&CPU::OpcodeCB_B4,&CPU::OpcodeCB_B5,&CPU::OpcodeCB_B6,&CPU::OpcodeCB_B7,&CPU::OpcodeCB_B8,&CPU::OpcodeCB_B9,&CPU::OpcodeCB_BA,&CPU::OpcodeCB_BB,&CPU::OpcodeCB_BC,&CPU::OpcodeCB_BD,&CPU::OpcodeCB_BE,&CPU::OpcodeCB_BF,
			&CPU::OpcodeCB_C0,&CPU::OpcodeCB_C1,&CPU::OpcodeCB_C2,&CPU::OpcodeCB_C3,&CPU::OpcodeCB_C4,&CPU::OpcodeCB_C5,&CPU::OpcodeCB_C6,&CPU::OpcodeCB_C7,&CPU::OpcodeCB_C8,&CPU::OpcodeCB_C9,&CPU::OpcodeCB_CA,&CPU::OpcodeCB_CB,&CPU::OpcodeCB_CC,&CPU::OpcodeCB_CD,&CPU::OpcodeCB_CE,&CPU::OpcodeCB_CF,
			&CPU::OpcodeCB_D0,&CPU::OpcodeCB_D1,&CPU::OpcodeCB_D2,&CPU::OpcodeCB_D3,&CPU::OpcodeCB_D4,&CPU::OpcodeCB_D5,&CPU::OpcodeCB_D6,&CPU::OpcodeCB_D7,&CPU::OpcodeCB_D8,&CPU::OpcodeCB_D9,&CPU::OpcodeCB_DA,&CPU::OpcodeCB_DB,&CPU::OpcodeCB_DC,&CPU::OpcodeCB_DD,&CPU::OpcodeCB_DE,&CPU::OpcodeCB_DF,
			&CPU::OpcodeCB_E0,&CPU::OpcodeCB_E1,&CPU::OpcodeCB_E2,&CPU::OpcodeCB_E3,&CPU::OpcodeCB_E4,&CPU::OpcodeCB_E5,&CPU::OpcodeCB_E6,&CPU::OpcodeCB_E7,&CPU::OpcodeCB_E8,&CPU::OpcodeCB_E9,&CPU::OpcodeCB_EA,&CPU::OpcodeCB_EB,&CPU::OpcodeCB_EC,&CPU::OpcodeCB_ED,&CPU::OpcodeCB_EE,&CPU::OpcodeCB_EF,
			&CPU::OpcodeCB_F0,&CPU::OpcodeCB_F1,&CPU::OpcodeCB_F2,&CPU::OpcodeCB_F3,&CPU::OpcodeCB_F4,&CPU::OpcodeCB_F5,&CPU::OpcodeCB_F6,&CPU::OpcodeCB_F7,&CPU::OpcodeCB_F8,&CPU::OpcodeCB_F9,&CPU::OpcodeCB_FA,&CPU::OpcodeCB_FB,&CPU::OpcodeCB_FC,&CPU::OpcodeCB_FD,&CPU::OpcodeCB_FE,&CPU::OpcodeCB_FF
		};

#pragma endregion

	#pragma region Fields
	private:
		Register af;
		Register bc;
		Register de;
		Register hl;
		Register pc;
		Register sp;

		MMU* mmu; // pointer to mmu
		ALU alu;

		u8 lastOpcode;
		int cycleCount;
		bool halt;
		bool stop;
		bool pendingDisableInterrupts;
		bool pendingEnableInterrupts;
		bool enableInterrupts;
	public:
		const int MAXCYCLES = 69905;

#pragma endregion

	#pragma region Methods
	public:
		CPU(MMU* mmu);
		~CPU();
		int ExecuteOpcode();
		void UpdateTimers();
		void CheckInterrupts();
		std::string PrintRegister(std::string registerToPrint);
		std::string PrintOpcode();
		void ResetCycleCount();
		bool IsUpdateFinished();

	private:
		CPU();
		u8 Load8BitImmediateValue();
		u16 Load16BitImmediateValue();
		void RunInterrupts(u8 bit);
	
		#pragma region Opcodes
		void Opcode00();
		void Opcode01();
		void Opcode02();
		void Opcode03();
		void Opcode04();
		void Opcode05();
		void Opcode06();
		void Opcode07();
		void Opcode08();
		void Opcode09();
		void Opcode0A();
		void Opcode0B();
		void Opcode0C();
		void Opcode0D();
		void Opcode0E();
		void Opcode0F();
		void Opcode10();
		void Opcode11();
		void Opcode12();
		void Opcode13();
		void Opcode14();
		void Opcode15();
		void Opcode16();
		void Opcode17();
		void Opcode18();
		void Opcode19();
		void Opcode1A();
		void Opcode1B();
		void Opcode1C();
		void Opcode1D();
		void Opcode1E();
		void Opcode1F();
		void Opcode20();
		void Opcode21();
		void Opcode22();
		void Opcode23();
		void Opcode24();
		void Opcode25();
		void Opcode26();
		void Opcode27();
		void Opcode28();
		void Opcode29();
		void Opcode2A();
		void Opcode2B();
		void Opcode2C();
		void Opcode2D();
		void Opcode2E();
		void Opcode2F();
		void Opcode30();
		void Opcode31();
		void Opcode32();
		void Opcode33();
		void Opcode34();
		void Opcode35();
		void Opcode36();
		void Opcode37();
		void Opcode38();
		void Opcode39();
		void Opcode3A();
		void Opcode3B();
		void Opcode3C();
		void Opcode3D();
		void Opcode3E();
		void Opcode3F();
		void Opcode40();
		void Opcode41();
		void Opcode42();
		void Opcode43();
		void Opcode44();
		void Opcode45();
		void Opcode46();
		void Opcode47();
		void Opcode48();
		void Opcode49();
		void Opcode4A();
		void Opcode4B();
		void Opcode4C();
		void Opcode4D();
		void Opcode4E();
		void Opcode4F();
		void Opcode50();
		void Opcode51();
		void Opcode52();
		void Opcode53();
		void Opcode54();
		void Opcode55();
		void Opcode56();
		void Opcode57();
		void Opcode58();
		void Opcode59();
		void Opcode5A();
		void Opcode5B();
		void Opcode5C();
		void Opcode5D();
		void Opcode5E();
		void Opcode5F();
		void Opcode60();
		void Opcode61();
		void Opcode62();
		void Opcode63();
		void Opcode64();
		void Opcode65();
		void Opcode66();
		void Opcode67();
		void Opcode68();
		void Opcode69();
		void Opcode6A();
		void Opcode6B();
		void Opcode6C();
		void Opcode6D();
		void Opcode6E();
		void Opcode6F();
		void Opcode70();
		void Opcode71();
		void Opcode72();
		void Opcode73();
		void Opcode74();
		void Opcode75();
		void Opcode76();
		void Opcode77();
		void Opcode78();
		void Opcode79();
		void Opcode7A();
		void Opcode7B();
		void Opcode7C();
		void Opcode7D();
		void Opcode7E();
		void Opcode7F();
		void Opcode80();
		void Opcode81();
		void Opcode82();
		void Opcode83();
		void Opcode84();
		void Opcode85();
		void Opcode86();
		void Opcode87();
		void Opcode88();
		void Opcode89();
		void Opcode8A();
		void Opcode8B();
		void Opcode8C();
		void Opcode8D();
		void Opcode8E();
		void Opcode8F();
		void Opcode90();
		void Opcode91();
		void Opcode92();
		void Opcode93();
		void Opcode94();
		void Opcode95();
		void Opcode96();
		void Opcode97();
		void Opcode98();
		void Opcode99();
		void Opcode9A();
		void Opcode9B();
		void Opcode9C();
		void Opcode9D();
		void Opcode9E();
		void Opcode9F();
		void OpcodeA0();
		void OpcodeA1();
		void OpcodeA2();
		void OpcodeA3();
		void OpcodeA4();
		void OpcodeA5();
		void OpcodeA6();
		void OpcodeA7();
		void OpcodeA8();
		void OpcodeA9();
		void OpcodeAA();
		void OpcodeAB();
		void OpcodeAC();
		void OpcodeAD();
		void OpcodeAE();
		void OpcodeAF();
		void OpcodeB0();
		void OpcodeB1();
		void OpcodeB2();
		void OpcodeB3();
		void OpcodeB4();
		void OpcodeB5();
		void OpcodeB6();
		void OpcodeB7();
		void OpcodeB8();
		void OpcodeB9();
		void OpcodeBA();
		void OpcodeBB();
		void OpcodeBC();
		void OpcodeBD();
		void OpcodeBE();
		void OpcodeBF();
		void OpcodeC0();
		void OpcodeC1();
		void OpcodeC2();
		void OpcodeC3();
		void OpcodeC4();
		void OpcodeC5();
		void OpcodeC6();
		void OpcodeC7();
		void OpcodeC8();
		void OpcodeC9();
		void OpcodeCA();
		void OpcodeCB();
		void OpcodeCC();
		void OpcodeCD();
		void OpcodeCE();
		void OpcodeCF();
		void OpcodeD0();
		void OpcodeD1();
		void OpcodeD2();
		void OpcodeD3();
		void OpcodeD4();
		void OpcodeD5();
		void OpcodeD6();
		void OpcodeD7();
		void OpcodeD8();
		void OpcodeD9();
		void OpcodeDA();
		void OpcodeDB();
		void OpcodeDC();
		void OpcodeDD();
		void OpcodeDE();
		void OpcodeDF();
		void OpcodeE0();
		void OpcodeE1();
		void OpcodeE2();
		void OpcodeE3();
		void OpcodeE4();
		void OpcodeE5();
		void OpcodeE6();
		void OpcodeE7();
		void OpcodeE8();
		void OpcodeE9();
		void OpcodeEA();
		void OpcodeEB();
		void OpcodeEC();
		void OpcodeED();
		void OpcodeEE();
		void OpcodeEF();
		void OpcodeF0();
		void OpcodeF1();
		void OpcodeF2();
		void OpcodeF3();
		void OpcodeF4();
		void OpcodeF5();
		void OpcodeF6();
		void OpcodeF7();
		void OpcodeF8();
		void OpcodeF9();
		void OpcodeFA();
		void OpcodeFB();
		void OpcodeFC();
		void OpcodeFD();
		void OpcodeFE();
		void OpcodeFF();

		void OpcodeCB_00();
		void OpcodeCB_01();
		void OpcodeCB_02();
		void OpcodeCB_03();
		void OpcodeCB_04();
		void OpcodeCB_05();
		void OpcodeCB_06();
		void OpcodeCB_07();
		void OpcodeCB_08();
		void OpcodeCB_09();
		void OpcodeCB_0A();
		void OpcodeCB_0B();
		void OpcodeCB_0C();
		void OpcodeCB_0D();
		void OpcodeCB_0E();
		void OpcodeCB_0F();
		void OpcodeCB_10();
		void OpcodeCB_11();
		void OpcodeCB_12();
		void OpcodeCB_13();
		void OpcodeCB_14();
		void OpcodeCB_15();
		void OpcodeCB_16();
		void OpcodeCB_17();
		void OpcodeCB_18();
		void OpcodeCB_19();
		void OpcodeCB_1A();
		void OpcodeCB_1B();
		void OpcodeCB_1C();
		void OpcodeCB_1D();
		void OpcodeCB_1E();
		void OpcodeCB_1F();
		void OpcodeCB_20();
		void OpcodeCB_21();
		void OpcodeCB_22();
		void OpcodeCB_23();
		void OpcodeCB_24();
		void OpcodeCB_25();
		void OpcodeCB_26();
		void OpcodeCB_27();
		void OpcodeCB_28();
		void OpcodeCB_29();
		void OpcodeCB_2A();
		void OpcodeCB_2B();
		void OpcodeCB_2C();
		void OpcodeCB_2D();
		void OpcodeCB_2E();
		void OpcodeCB_2F();
		void OpcodeCB_30();
		void OpcodeCB_31();
		void OpcodeCB_32();
		void OpcodeCB_33();
		void OpcodeCB_34();
		void OpcodeCB_35();
		void OpcodeCB_36();
		void OpcodeCB_37();
		void OpcodeCB_38();
		void OpcodeCB_39();
		void OpcodeCB_3A();
		void OpcodeCB_3B();
		void OpcodeCB_3C();
		void OpcodeCB_3D();
		void OpcodeCB_3E();
		void OpcodeCB_3F();
		void OpcodeCB_40();
		void OpcodeCB_41();
		void OpcodeCB_42();
		void OpcodeCB_43();
		void OpcodeCB_44();
		void OpcodeCB_45();
		void OpcodeCB_46();
		void OpcodeCB_47();
		void OpcodeCB_48();
		void OpcodeCB_49();
		void OpcodeCB_4A();
		void OpcodeCB_4B();
		void OpcodeCB_4C();
		void OpcodeCB_4D();
		void OpcodeCB_4E();
		void OpcodeCB_4F();
		void OpcodeCB_50();
		void OpcodeCB_51();
		void OpcodeCB_52();
		void OpcodeCB_53();
		void OpcodeCB_54();
		void OpcodeCB_55();
		void OpcodeCB_56();
		void OpcodeCB_57();
		void OpcodeCB_58();
		void OpcodeCB_59();
		void OpcodeCB_5A();
		void OpcodeCB_5B();
		void OpcodeCB_5C();
		void OpcodeCB_5D();
		void OpcodeCB_5E();
		void OpcodeCB_5F();
		void OpcodeCB_60();
		void OpcodeCB_61();
		void OpcodeCB_62();
		void OpcodeCB_63();
		void OpcodeCB_64();
		void OpcodeCB_65();
		void OpcodeCB_66();
		void OpcodeCB_67();
		void OpcodeCB_68();
		void OpcodeCB_69();
		void OpcodeCB_6A();
		void OpcodeCB_6B();
		void OpcodeCB_6C();
		void OpcodeCB_6D();
		void OpcodeCB_6E();
		void OpcodeCB_6F();
		void OpcodeCB_70();
		void OpcodeCB_71();
		void OpcodeCB_72();
		void OpcodeCB_73();
		void OpcodeCB_74();
		void OpcodeCB_75();
		void OpcodeCB_76();
		void OpcodeCB_77();
		void OpcodeCB_78();
		void OpcodeCB_79();
		void OpcodeCB_7A();
		void OpcodeCB_7B();
		void OpcodeCB_7C();
		void OpcodeCB_7D();
		void OpcodeCB_7E();
		void OpcodeCB_7F();
		void OpcodeCB_80();
		void OpcodeCB_81();
		void OpcodeCB_82();
		void OpcodeCB_83();
		void OpcodeCB_84();
		void OpcodeCB_85();
		void OpcodeCB_86();
		void OpcodeCB_87();
		void OpcodeCB_88();
		void OpcodeCB_89();
		void OpcodeCB_8A();
		void OpcodeCB_8B();
		void OpcodeCB_8C();
		void OpcodeCB_8D();
		void OpcodeCB_8E();
		void OpcodeCB_8F();
		void OpcodeCB_90();
		void OpcodeCB_91();
		void OpcodeCB_92();
		void OpcodeCB_93();
		void OpcodeCB_94();
		void OpcodeCB_95();
		void OpcodeCB_96();
		void OpcodeCB_97();
		void OpcodeCB_98();
		void OpcodeCB_99();
		void OpcodeCB_9A();
		void OpcodeCB_9B();
		void OpcodeCB_9C();
		void OpcodeCB_9D();
		void OpcodeCB_9E();
		void OpcodeCB_9F();
		void OpcodeCB_A0();
		void OpcodeCB_A1();
		void OpcodeCB_A2();
		void OpcodeCB_A3();
		void OpcodeCB_A4();
		void OpcodeCB_A5();
		void OpcodeCB_A6();
		void OpcodeCB_A7();
		void OpcodeCB_A8();
		void OpcodeCB_A9();
		void OpcodeCB_AA();
		void OpcodeCB_AB();
		void OpcodeCB_AC();
		void OpcodeCB_AD();
		void OpcodeCB_AE();
		void OpcodeCB_AF();
		void OpcodeCB_B0();
		void OpcodeCB_B1();
		void OpcodeCB_B2();
		void OpcodeCB_B3();
		void OpcodeCB_B4();
		void OpcodeCB_B5();
		void OpcodeCB_B6();
		void OpcodeCB_B7();
		void OpcodeCB_B8();
		void OpcodeCB_B9();
		void OpcodeCB_BA();
		void OpcodeCB_BB();
		void OpcodeCB_BC();
		void OpcodeCB_BD();
		void OpcodeCB_BE();
		void OpcodeCB_BF();
		void OpcodeCB_C0();
		void OpcodeCB_C1();
		void OpcodeCB_C2();
		void OpcodeCB_C3();
		void OpcodeCB_C4();
		void OpcodeCB_C5();
		void OpcodeCB_C6();
		void OpcodeCB_C7();
		void OpcodeCB_C8();
		void OpcodeCB_C9();
		void OpcodeCB_CA();
		void OpcodeCB_CB();
		void OpcodeCB_CC();
		void OpcodeCB_CD();
		void OpcodeCB_CE();
		void OpcodeCB_CF();
		void OpcodeCB_D0();
		void OpcodeCB_D1();
		void OpcodeCB_D2();
		void OpcodeCB_D3();
		void OpcodeCB_D4();
		void OpcodeCB_D5();
		void OpcodeCB_D6();
		void OpcodeCB_FF();
		void OpcodeCB_D8();
		void OpcodeCB_D9();
		void OpcodeCB_DA();
		void OpcodeCB_DB();
		void OpcodeCB_DC();
		void OpcodeCB_DD();
		void OpcodeCB_DE();
		void OpcodeCB_DF();
		void OpcodeCB_E0();
		void OpcodeCB_E1();
		void OpcodeCB_E2();
		void OpcodeCB_E3();
		void OpcodeCB_D7();
		void OpcodeCB_E4();
		void OpcodeCB_E5();
		void OpcodeCB_E6();
		void OpcodeCB_E7();
		void OpcodeCB_E8();
		void OpcodeCB_E9();
		void OpcodeCB_EA();
		void OpcodeCB_EB();
		void OpcodeCB_EC();
		void OpcodeCB_ED();
		void OpcodeCB_EE();
		void OpcodeCB_EF();
		void OpcodeCB_F0();
		void OpcodeCB_F1();
		void OpcodeCB_F2();
		void OpcodeCB_F3();
		void OpcodeCB_F4();
		void OpcodeCB_F5();
		void OpcodeCB_F6();
		void OpcodeCB_F7();
		void OpcodeCB_F8();
		void OpcodeCB_F9();
		void OpcodeCB_FA();
		void OpcodeCB_FB();
		void OpcodeCB_FC();
		void OpcodeCB_FD();
		void OpcodeCB_FE();
#pragma endregion

		//8-Bit Load Methods
		void LD(u8& reg, u8 value);
		// 16-Bit Load Methods
		void LD(u16& reg, u16 value);
		void Push(u16 value);
		u16 Pop();
		void Swap(u8& n);
		void RLCn(u8& n);
		void RLn(u8& n);
		void RRCn(u8& n);
		void RRn(u8& n);
		void SLAn(u8& n);
		void SRAn(u8& n);
		void SRLn(u8& n);
		void BITbr(u8 bit, u8& r);
		void SETbr(u8 bit, u8& r);
		void RESbr(u8 bit, u8& r);
#pragma endregion

	};
}
