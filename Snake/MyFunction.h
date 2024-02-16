#pragma once
#include <iostream>
#include <Windows.h>

struct Point
{
	int x{ 0 }, y{ 0 };
};

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}