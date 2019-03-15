#include "Emulator.h"
#include "Debug.h"
#include <fstream>
//#include "SDL.h"

using namespace Gameboy;

Emulator::Emulator(void) : isRunning(false), romLoaded(false)
{
	cartridgeMemory = new char[0x200000];

	mmu.reset(new MMU());
	// setup the CPU
	cpu.reset(new CPU(mmu.get()));
}


Emulator::~Emulator(void)
{
	cpu.release();
	mmu.release();	
}

bool Emulator::Initialize()
{

	return true;
}

void Emulator::LoadROM(std::string romPath)
{
	std::fstream in(romPath, std::fstream::in | std::fstream::binary);

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
	romLoaded = true;
}

std::string Emulator::PrintCPU()
{
	return Debug::Print(*cpu);
}

void Emulator::Run()
{
	if (romLoaded && !isRunning)
	{
		cpu->ResetCycleCount();

		while (!cpu->IsUpdateFinished())
		{
			Step();
		}
	}
}

void Emulator::Shutdown()
{
	delete[] cartridgeMemory;
}

void Emulator::Pause(bool shouldPause)
{
	isRunning = shouldPause;
}

void Emulator::Step()
{
	int cycles = cpu->ExecuteOpcode();
	cpu->UpdateTimers();
	//ppu.UpdateGraphics(cycles);
	cpu->CheckInterrupts();
}
