#pragma once
typedef unsigned char byte;

class Memory
{
private:
	byte m_memory[0xFFFF];
public:
	Memory(void);
	bool Initialize();

#pragma region Operator Overloads
	byte& operator[](int i) { return m_memory[i]; }
#pragma endregion
};




