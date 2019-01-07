#pragma once
#include <CPU.h>
#include <Register.h>

class Debug
{
public:
	static std::string Print(Gameboy::CPU cpu);

	static void ClearScreen();
};

