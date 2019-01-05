#pragma once
#include <CPU.h>
#include <Register.h>

class Debug
{
public:
	static void Print(Gameboy::CPU cpu);

	static void ClearScreen();
};

