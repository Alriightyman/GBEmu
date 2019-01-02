#include "Emulator.h"
#include "Debug.h"
#include <fstream>
using namespace Gameboy;

Emulator::Emulator(void) : m_isRunning(false)
{
	cartridgeMemory = new char[0x200000];

	// setup the CPU
	cpu.reset(new CPU(mmu.get()));
}


Emulator::~Emulator(void)
{

}

bool Emulator::Initialize()
{

	return true;
}

void Emulator::LoadROM(const char * rom)
{
	std::fstream is(rom, std::fstream::in | std::fstream::binary);

	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);

	try
	{
		is.read((char*)cartridgeMemory, length);
	}
	catch (const std::exception&)
	{
		is.close();
	}
	 
	is.close();
}

void Emulator::Run()
{
	while (!cpu->IsUpdateFinished())
	{
		int cycles = cpu->ExecuteOpcode();
		Debug::Print(*cpu);
		cpu->UpdateTimers();
		//ppu.UpdateGraphics(cycles);
		cpu->RunInterrupts();
	}

	// RenderScreen();
}

void Emulator::Shutdown()
{
}
