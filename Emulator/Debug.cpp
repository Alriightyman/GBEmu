#include "Debug.h"
#include <iostream>
#include <windows.h>
using namespace std;

void Debug::Print(Cpu c)
{
	ClearScreen();
	cout << "Registers" << endl;
	cout << "A: " << static_cast<unsigned int>(c.GetRegA()) << endl;
	cout << "B: " << static_cast<unsigned int>(c.GetRegB()) << " C: " << static_cast<unsigned int>(c.GetRegC()) << endl;
	cout << "D: " << static_cast<unsigned int>(c.GetRegD()) << " E: " << static_cast<unsigned int>(c.GetRegE()) << endl;
	cout << "H: " << static_cast<unsigned int>(c.GetRegH()) << " L: " << static_cast<unsigned int>(c.GetRegL()) << endl;
	cout << "Flags\n" << "z n h c\n" << static_cast<unsigned int>(c.GetFlag(ZFlag)) <<" "<< static_cast<unsigned int>(c.GetFlag(NFlag))
							<<" "<< static_cast<unsigned int>(c.GetFlag(HFlag)) <<" "<< static_cast<unsigned int>(c.GetFlag(CFlag)) << endl;
}
void Debug::ClearScreen()
{
#ifdef _DEBUG
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
	hStdOut,
	(TCHAR) ' ',
	cellCount,
	homeCoords,
	&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
	hStdOut,
	csbi.wAttributes,
	cellCount,
	homeCoords,
	&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
#endif
}