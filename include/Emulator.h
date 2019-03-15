#pragma once
#include <CPU.h>
#include <memory>
#include <string>

class Emulator
{
private:
	std::unique_ptr<Gameboy::CPU> cpu;
	std::unique_ptr<Gameboy::MMU> mmu;

	bool isRunning;
	char* cartridgeMemory; // [0x200000];
	bool romLoaded;

public:
	Emulator(void);
	~Emulator(void);
	bool Initialize();
	void LoadROM(std::string romPath);
	std::string PrintCPU();
	void Run();
	void Shutdown();
	void Pause(bool shouldPause);
	void Step();

	Gameboy::CPU* GetCPU() const { return cpu.get(); } ;
};

