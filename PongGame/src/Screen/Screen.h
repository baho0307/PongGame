#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>

class Screen
{
public:
	Screen(std::vector<int> *inf_addr, std::map<int, char> texture, int x = 0, int y = 0);
	void				Update();
	void				SetCoord(int x, int y);
private:
	std::vector<int>	*addr;
	std::string			prevBuffer;
	std::string			scrBuffer;
	std::map<int, char>	texture;
	int					p_X;
	int					p_Y;
	void				Calc();
	void				Swap();
	void				setCursorPosition(int x, int y);
};

