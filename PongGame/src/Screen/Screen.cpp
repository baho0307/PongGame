#include "Screen.h"

void Screen::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Screen::Calc()
{
	prevBuffer = "";
	for (int i : *addr)
		prevBuffer += texture[i];
}

Screen::Screen(std::vector<int> *inf_addr, std::map<int, char> texture, int x = 0, int y = 0)
{
	this->addr = inf_addr;
	this->texture = texture;
	this->p_X = x;
	this->p_Y = y;
	scrBuffer = "";
}

void Screen::Swap()
{
	std::string	tmp;

	tmp = prevBuffer;
	prevBuffer = scrBuffer;
	scrBuffer = tmp;
}

void Screen::Update()
{
	Calc();
	Swap();
	if (prevBuffer == "")
		std::cout << scrBuffer;
	else
	{
		for (int i = 0; i < scrBuffer.size(); i++)
		{
			if (scrBuffer[i] != prevBuffer[i])
			{
				setCursorPosition((i % 120) + p_X, (i / 120) + p_Y);
				std::cout << scrBuffer[i];
			}
		}
	}
}

void Screen::SetCoord(int x, int y)
{
	this->p_X = x;
	this->p_Y = y;
}
