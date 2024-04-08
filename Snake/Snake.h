#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include <Windows.h>
#include "Keyboard.h"
#include "MyFunction.h"

class Snake : Keyboard
{
	static const int WIDTH{ 40 };
	static const int HEIGHT{ 18 };
	static const int MAX_LEN_SNAKE{ (WIDTH - 3) * (HEIGHT - 2) };

	char snake = 'O';
	COORD pSnake[MAX_LEN_SNAKE] = {0, 0};
	float speed{ 0 };

	enum MOVE { UP, DOWN, LEFT, RIGTH };

	char food = '*';
	COORD pFood{ 0, 0 };

	int len{ 1 };

	int snake_dir;

	bool is_run = true;

	char map[(WIDTH * HEIGHT) + 1] = {
		"#######################################\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#                                     #\n"
		"#######################################\n" };

	// Обработка нажатий.
	void KeyDown()
	{
		// Нажатие W.
		if (EventHandler(0x57) || EventHandler(VK_UP))
		{
			if (snake_dir != DOWN)
				snake_dir = UP;
		}
		// Нажатие D.
		if (EventHandler(0x53) || EventHandler(VK_DOWN))
		{
			if (snake_dir != UP)
				snake_dir = DOWN;
		}
		// Нажатие A.
		if (EventHandler(0x41) || EventHandler(VK_LEFT))
		{
			if (snake_dir != RIGTH)
				snake_dir = LEFT;
		}
		// Нажатие D.
		if (EventHandler(0x44) || EventHandler(VK_RIGHT))
		{
			if (snake_dir != LEFT)
				snake_dir = RIGTH;
		}
		// Нажатие Escape.
		if (EventHandler(VK_ESCAPE))
		{
			is_run = false;
		}
	}

	// Стартовые данные.
	void StartSettings()
	{
		snake_dir = UP;
		speed = 1;
		pSnake[0] = { (short)WIDTH / 2, (short)HEIGHT / 2 };
		pFood = { (short)(1 + rand() % (WIDTH - 3)), (short)(1 + rand() % (HEIGHT - 2)) };
	}

	// Проверка съела ли змейка еду.
	void IsEatFood()
	{
		if (pSnake[0].X == pFood.X && pSnake[0].Y == pFood.Y)
		{
			len++;
			pFood = { (short)(1 + rand() % (WIDTH - 3)), (short)(1 + rand() % (HEIGHT - 2)) };
		}
	}

	// Проверка на проигрыш.
	bool IsLoss()
	{
		// Проверка на столкновение со стеной.
		if (pSnake[0].X == 0 || pSnake[0].Y == 0 || pSnake[0].X == WIDTH - 2 || pSnake[0].Y == HEIGHT - 1)
			return true;

		for (size_t i = 1; i < len; i++)
		{
			if (pSnake[0].X == pSnake[i].X && pSnake[0].Y == pSnake[i].Y)
			{
				i = len;
				return true;
			}
		}
		return false;
	}

	// Движение змейки.
	void MoveSnake()
	{
		for (int i = len - 2; i >= 0; --i)
			pSnake[i + 1] = pSnake[i];

		if (snake_dir == UP)
			--pSnake[0].Y;

		if (snake_dir == DOWN)
			++pSnake[0].Y;

		if (snake_dir == RIGTH)
			++pSnake[0].X;

		if (snake_dir == LEFT)
			--pSnake[0].X;
	}

	// Отрисовка экрана.
	void Screen()
	{
		gotoxy(0, 0);
		std::cout << "Length = " << len << "\tSpeed = " << speed << "\n";
		map[pFood.Y * WIDTH + pFood.X] = food;
		for (size_t i = 0; i < len; i++)
			map[pSnake[i].Y * WIDTH + pSnake[i].X] = snake;

		std::cout << map;

		for (size_t i = 0; i < len; i++)
			map[pSnake[i].Y * WIDTH + pSnake[i].X] = ' ';
	}

	//
	void Final() const
	{
		if (is_run)
		{
			gotoxy(13, HEIGHT / 2);
			std::cout << "\x1b[31mТы проиграл!\x1b[0m";
			gotoxy(WIDTH, HEIGHT);
		}
		else
		{
			gotoxy(13, HEIGHT / 2);
			std::cout << "\x1b[31mИгра завершена!\x1b[0m";
			gotoxy(WIDTH, HEIGHT);
		}
	}

public:
	//
	void Play()
	{
		StartSettings();

		double time = clock();

		do
		{
			KeyDown();

			if ((clock() - time) / CLOCKS_PER_SEC >= 0.8)
			{
				time = clock();

				IsEatFood();

				MoveSnake();

				Screen();
			}
		} while (!IsLoss() && is_run);

		Final();
	}
};

#endif // _SNAKE_H_