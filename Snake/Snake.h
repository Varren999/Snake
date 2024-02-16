#pragma once
#include <iostream>
#include <Windows.h>
#include "Keyboard.h"
#include "MyFunction.h"

class Snake : Keyboard
{
	static const int WIDTH{ 40 }, HEIGHT{ 18 }, MAX_LEN_SNAKE{ (WIDTH - 3) * (HEIGHT - 2) };

	char snake = 'O';
	int snake_x[MAX_LEN_SNAKE] = { 0 };
	int snake_y[MAX_LEN_SNAKE] = { 0 };
	float speed{ 0 };

	enum MOVE { UP, DOWN, LEFT, RIGTH };

	char food = '*';
	int food_x{ 0 }, food_y{ 0 };

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
		if (EventHandler(0x57))
		{
			if (snake_dir != DOWN)
				snake_dir = UP;
		}
		// Нажатие D.
		if (EventHandler(0x53))
		{
			if (snake_dir != UP)
				snake_dir = DOWN;
		}
		// Нажатие A.
		if (EventHandler(0x41))
		{
			if (snake_dir != RIGTH)
				snake_dir = LEFT;
		}
		// Нажатие D.
		if (EventHandler(0x44))
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
		snake_x[0] = WIDTH / 2;
		snake_y[0] = HEIGHT / 2;
		food_x = 1 + rand() % (WIDTH - 3);
		food_y = 1 + rand() % (HEIGHT - 2);
	}

	// Проверка съела ли змейка еду.
	void IsEatFood()
	{
		if (snake_x[0] == food_x && snake_y[0] == food_y)
		{
			len++;
			food_x = 1 + rand() % (WIDTH - 3);
			food_y = 1 + rand() % (HEIGHT - 2);
		}
	}

	// Проверка на проигрыш.
	bool IsLoss()
	{
		if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1)
			return true;

		for (size_t i = 1; i < len; i++)
		{
			if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
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
		{
			snake_x[i + 1] = snake_x[i];
			snake_y[i + 1] = snake_y[i];
		}

		if (snake_dir == UP)
			--snake_y[0];

		if (snake_dir == DOWN)
			++snake_y[0];

		if (snake_dir == RIGTH)
			++snake_x[0];

		if (snake_dir == LEFT)
			--snake_x[0];
	}

	// Отрисовка экрана.
	void Screen()
	{
		gotoxy(0, 0);
		std::cout << "Length = " << len << "\tSpeed = " << speed << "\n";
		map[food_y * WIDTH + food_x] = food;
		for (size_t i = 0; i < len; i++)
		{
			map[snake_y[i] * WIDTH + snake_x[i]] = snake;
		}
		std::cout << map;
		for (size_t i = 0; i < len; i++)
		{
			map[snake_y[i] * WIDTH + snake_x[i]] = ' ';
		}
	}

	//
	void Final()
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