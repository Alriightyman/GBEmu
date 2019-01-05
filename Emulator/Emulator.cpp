#include "Emulator.h"
#include "Debug.h"
#include <fstream>
using namespace Gameboy;

Emulator::Emulator(void) : m_isRunning(false)
{
	cartridgeMemory = new char[0x200000];

	mmu.reset(new MMU());
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
	std::fstream in(rom, std::fstream::in | std::fstream::binary);

	in.seekg(0, in.end);
	int length = in.tellg();
	in.seekg(0, in.beg);

	try
	{
		in.read(cartridgeMemory, length);
	}
	catch (const std::exception&)
	{
		in.close();
	}
	 
	in.close();

	mmu->LoadROM((s8*)cartridgeMemory, length);
}

void Emulator::Run()
{
	cpu->ResetCycleCount();

	while (!cpu->IsUpdateFinished())
	{
		int cycles = cpu->ExecuteOpcode();
		//Debug::ClearScreen();
		Debug::Print(*cpu);
		cpu->UpdateTimers();
		//ppu.UpdateGraphics(cycles);
		cpu->CheckInterrupts();
	}

	// RenderScreen();
}

void Emulator::Shutdown()
{
}
