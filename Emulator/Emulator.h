#pragma once
#include <Cpu.h>
#include <Video.h>

class Emulator
{
private:
	// gameboy processor
	Cpu m_cpu;
	// gameboy memory
	Memory m_memory;
	// gameboy sound

	// gameboy video
	Video m_video;

	bool m_isRunning;
public:
	Emulator(void);
	~Emulator(void);
	bool Initialize();

	void Run();
	void Shutdown();
};

