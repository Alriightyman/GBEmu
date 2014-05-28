#include "Memory.h"


Memory::Memory(void)
{

}


bool Memory::Initialize()
{
	m_memory = new byte[0xFFFF];
	return true;
}
