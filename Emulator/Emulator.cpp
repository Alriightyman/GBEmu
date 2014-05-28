#include "Emulator.h"
#include "Debug.h"

Emulator::Emulator(void) : m_isRunning(false)
{
}


Emulator::~Emulator(void)
{
}

bool Emulator::Initialize()
{
	if(!m_cpu.Initialize())
		return false;

	if(!m_memory.Initialize())
		return false;

	if(!m_video.Initialize())
		return false;

	return true;
}

void Emulator::Run()
{
	if ( m_isRunning)
		m_cpu.Run(m_memory);

	m_video.Run();

	Debug::Print(m_cpu);
}