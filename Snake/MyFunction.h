#pragma once
#ifndef _MYFUNCTION_H_
#define _MYFUNCTION_H_

#include <iostream>
#include <Windows.h>

/// <summary>
/// Метод переводит курсор в указаную позицию.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

#endif // _MYFUNCTION_H_