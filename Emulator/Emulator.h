#pragma once


class Emulator
{
private:

	bool m_isRunning;
public:
	Emulator(void);
	~Emulator(void);
	bool Initialize();

	void Run();
	void Shutdown();
};

