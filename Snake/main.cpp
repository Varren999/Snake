#include <iostream>
#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

const int WIDTH = 40;
const int HEIGHT = 18;
const int MAX_LEN_PHYITON = (WIDTH - 3) * (HEIGHT - 2);
enum MOVE { UP, DOWN, LEFT, RIGTH };

int snake_dir = UP;

int food_x = 1 + rand() % (WIDTH - 3);
int food_y = 1 + rand() % (HEIGHT - 2);
char food = '*';

bool is_run = true;

char map[] = {
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

char snake = 'O';

int snake_x[MAX_LEN_PHYITON] = { 0 };
int snake_y[MAX_LEN_PHYITON] = { 0 };
int len = 1;

int main()
{
	setlocale(0, "");
	snake_x[0] = WIDTH / 2;
	snake_y[0] = HEIGHT / 2;
	double time = clock();
	while (is_run)
	{
		if (GetKeyState('W') & 0x8000)
		{
			if (snake_dir != DOWN)
				snake_dir = UP;
		}

		if (GetKeyState('S') & 0x8000)
		{
			if (snake_dir != UP)
				snake_dir = DOWN;
		}

		if (GetKeyState('A') & 0x8000)
		{
			if (snake_dir != RIGTH)
				snake_dir = LEFT;
		}

		if (GetKeyState('D') & 0x8000)
		{
			if (snake_dir != LEFT)
				snake_dir = RIGTH;
		}

		if ((clock() - time) / CLOCKS_PER_SEC >= 0.3)
		{
			time = clock();

			if (snake_x[0] == food_x && snake_y[0] == food_y)
			{
				len++;
				food_x = 1 + rand() % (WIDTH - 3);
				food_y = 1 + rand() % (HEIGHT - 2);
			}

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

			if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1)
				is_run = false;

			for (int i = 1; i < len; i++)
			{
				if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
				{
					is_run = false;
					i = len;
				}
			}

			gotoxy(0, 0);
			std::cout << "Length = " << len << "\n";
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
	}
	gotoxy(13, HEIGHT / 2);
	std::cout << "\x1b[31mТы проиграл!\x1b[0m";
	gotoxy(WIDTH, HEIGHT);
	return 0;
}