#pragma once
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <Windows.h>

class Keyboard
{
public:
	Keyboard() = default;
	~Keyboard() = default;
	// Обработка нажатий клавиш.
	bool EventHandler(int Event)
	{
		if (GetAsyncKeyState(Event) & 0x8000)
		{
			Sleep(150);
			return true;
		}
		else
			return false;
	}
	// Функция чистит буфер ввода.
	void ClearBuffer()
	{
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		FlushConsoleInputBuffer(hStdin);
	}
};

#endif // _KEYBOARD_H_