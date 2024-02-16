#pragma once
#ifndef _MYFUNCTION_H_
#define _MYFUNCTION_H_

#include <iostream>
#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

#endif // _MYFUNCTION_H_