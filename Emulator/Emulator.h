#pragma once
#include <CPU.h>
#include <memory>

class Emulator
{
private:
	std::unique_ptr<Gameboy::CPU> cpu;
	std::unique_ptr<Gameboy::MMU> mmu;

	bool m_isRunning;
	char* cartridgeMemory; // [0x200000];
public:
	Emulator(void);
	~Emulator(void);
	bool Initialize();
	void LoadROM(const char* rom);

	void Run();
	void Shutdown();
};

