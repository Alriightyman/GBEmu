#pragma once
typedef unsigned char byte;

class Memory
{
private:
	byte m_memory[0xFFFF];
public:
	Memory(void);
	~Memory(void);

#pragma region Operator Overloads
	byte& operator[](int i) { return m_memory[i]; }
#pragma endregion
};




