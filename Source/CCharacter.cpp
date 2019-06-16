#pragma once
#include "CCharacter.h"
#define MAX 1024 
Character::Character(){}
Character::Character(const char *filename)
{
	ifstream fin(filename);
	width = height = 0;
	char buf[MAX + 1];
	while (!fin.eof())
	{
		fin.getline(buf, MAX);
		str.push_back(string(buf));
		height++;
	}
	width = str[0].length();
}
void Character::Set(const char* name)
{
	if (!str.empty())
	{
		str.clear();
	}
	ifstream fin(name);
	width = height = 0;
	char buf[MAX + 1];
	while (!fin.eof())
	{
		fin.getline(buf, MAX);
		str.push_back(string(buf));
		height++;
	}
	width = str[0].length();
}
string Character::Get(const char *name)
{
	wifstream wfin(name);
	wfin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstringstream wss;
	wss << wfin.rdbuf();
	wstring wstr= wss.str();
	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	char* m = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, m, bufferSize, NULL, NULL);

	string temp(m);
	delete[] m;
	return temp;
}
vector<string>& Character::Get()
{
	return str;
}
void Character::Draw(COORD coord, bool shap)
{
	Draw(coord.X, coord.Y, shap);
}
void Character::Draw(int x, int y, bool shap)
{
	if (shap)
	{
		if (x > BOARD_GAME_LEFT)
		{
			if (x + width - 1 < BOARD_GAME_RIGHT)
			{
				for (int i = 0; i < height; i++) {
					GotoXY(x, y + i);
					printf("%s", str[i].c_str());
				}
			}
			else
			{
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < BOARD_GAME_RIGHT-x; j++)
					{
						GotoXY(x + j, i + y);
						printf("%c", str[i].c_str()[j]);
					}
				}
			}
		}
		else
		{
			int index = BOARD_GAME_LEFT - x + 1;
			for (int i = 0; i < height; i++)
			{
				GotoXY(BOARD_GAME_LEFT + 1, y + i);
				printf("%s", str[i].c_str() + index);
			}
		}
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			GotoXY(x, y + i);
			printf("%s", str[i].c_str());

		}
	}
}
int Character::Width()
{
	return width;
}
int Character::Height()
{
	return height;
}
void Character::Write(ostream & out)
{
	out.write((char *)&width, sizeof(width));
	out.write((char*)&height, sizeof(height));
	for (int i = 0; i < height; i++)
	{
		int length = str[i].length();
		out.write((char*)&length, sizeof(length));
		out.write(str[i].c_str(), sizeof(char)*length);

	}
}
void Character::Read(istream &in)
{
	in.read((char*)&width, sizeof(width));
	in.read((char*)&height, sizeof(height));

	str.resize(height);
	int length;

	for (int i = 0; i < height; i++) {
		in.read((char*)&length, sizeof(length));
		str[i].resize(length);
		in.read((char*)&str[i][0], sizeof(char)*length);
	}
}
Character Character::operator+(Character & cha)
{
	if (height != cha.height) {
		return *this;
	}

	Character Character;

	for (int i = 0; i < height; i++) {
		Character.str.push_back(str[i] + cha.str[i]);
	}

	Character.width = width + cha.width;
	Character.height = height;

	return Character;
}

