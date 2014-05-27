#pragma once
#include "Cpu.h"
#include "Memory.h"

class Debug
{
public:
	static void Print(Cpu c);
	static void Print(Memory mem);
private:
	static void ClearScreen();
};

