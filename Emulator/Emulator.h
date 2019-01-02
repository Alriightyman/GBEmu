#pragma once
#include <CPU.h>

class Emulator
{
private:
	Gameboy::CPU cpu;
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

