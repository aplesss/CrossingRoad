#include "CMenuGame.h"
MenuGame::MenuGame()
{
	_H = CONSOLE_MENU_HEIGHT;
	_W = CONSOLE_MENU_WIDTH;
	SetMenu("main");
	PastRow = 3;
	CurrRow = 4;
}
MenuGame::MenuGame(int W, int H)
{
	_W = W;
	_H = H;
	SetMenu("main");
	PastRow = 3;
	CurrRow = 4;
}
int MenuGame::FindMidH()
{
	return _H / 2 - Menucha.Height() / 2 - Menucha.Height() % 2;
}
int MenuGame::FindMidW(string Title)
{
	return _W / 2 - Title.length() / 2 - Title.length() % 2;
}
int MenuGame::FindLongestPos(vector<string> text)
{
	int pos, longest = text[0].length();
	for (int i = 0; i < text.size(); i++)
	{
		if (longest  < text[i].length())
		{
			longest  = text[i].length();
			pos = i;
		}
	}
	return pos;
}
void MenuGame::SetMenu(const char* Type)
{
	if (strcmp(Type, "main") == 0)
		Menucha.Set("Character\\Main_Menu.txt");
	else if (strcmp(Type, "pause") == 0)
		Menucha.Set("Character\\Pause_Menu.txt");
	else if (strcmp(Type, "lose") == 0)
		Menucha.Set("Character\\Lose_Menu.txt");
	else if (strcmp(Type, "yes_no") == 0)
		Menucha.Set("Character\\Yes_No_Menu.txt");
	else if(strcmp(Type,"continue")==0)
		Menucha.Set("Character\\Continue_Menu.txt");
	else if (strcmp(Type, "setting") == 0)
		Menucha.Set("Character\\Setting_Menu.txt");
	else if (strcmp(Type, "on_off") == 0)
		Menucha.Set("Character\\On_Off_Menu.txt");
	Guide.Set("Character\\Guide.txt");
}
void MenuGame::Up()
{
	if (CurrRow == 4)
		return;
	PastRow = CurrRow;
	CurrRow--;
}
void MenuGame::Down()
{
	if (CurrRow == Menucha.Height() - 5) return;
	PastRow = CurrRow;
	CurrRow++;
}
void MenuGame::Clear()
{
	int x, y;
	vector<string> str = Menucha.Get();
	string temp="";
	for (int row = 0; row < Menucha.Height();row++)
	{
		int sizes = str[row].length();
		for (int i = 0; i < sizes; i++)
		{
			temp += " ";
		}
		temp += " ";
		x = FindMidW(str[row]) - 1;
		y = FindMidH() + row;
		GotoXY(x, y);
		printf("%s", temp.c_str());
	}
}
void MenuGame::Draw()

{
	short x, y;
	vector<string> str = Menucha.Get();
	for (int row = 0; row < Menucha.Height(); row++)
	{
		x =FindMidW(str[row]) - 1;
		y = FindMidH() + row;
		GotoXY(x, y);
		if (CurrRow == row)
		{
			TextColor(10);
			printf("->%s", str[row].c_str());
		}
		else if (PastRow == row && PastRow != 1)
		{
			TextColor(11);
			printf(" %s ", str[row].c_str());
		}
		else if (row == 1 || row ==Menucha.Height() - 1 - 1)
		{
			TextColor(15);
			printf(" %s ", str[row].c_str());
		}
		else if (row == 0 || row == Menucha.Height() - 1)
		{
			TextColor(9);
			printf(" %s ", str[row].c_str());
		}
		else
		{
			TextColor(11);
			printf(" %s ", str[row].c_str());
		}
	}
}
string MenuGame::Slection(bool sound)
{
	CurrRow = 4;
	PastRow = 3;
	Draw();
	while (true)
	{
		char ch = toupper(_getch());
		switch (ch)
		{
		case'W':
		case UP:
			this->Up(); if(sound)PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC); break;
		case'S':
		case DOWN:
			this->Down(); if (sound) PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC); break;
		case ENTER:
			TextColor(15);
			if (sound) PlaySound("Sound\\sfx_menu_select4.wav", NULL, SND_ASYNC);
			return Menucha.Get()[CurrRow];	
		}
		Draw();
		Sleep(50);
	}
}
void MenuGame::DrawGuide()
{
	GotoXY(0, 0);
	vector<string> str = Guide.Get();
	TextColor(FOREGROUND_WHITE);
	for (int row = 0; row < Guide.Height(); row++)
		printf("%s\n", str[row].c_str());
}
MenuGame::~MenuGame()
{
}
void MenuGame::ClearMenu()
{
	int x, y;
	vector<string> str = Menucha.Get();
	string temp = "";
	for (int row  = 0; row < Menucha.Height(); row++)
	{
		int sizes = str[row].length();

		for (int i = 0; i < sizes; i++) {
			temp += " ";
		}

		x = FindMidW(str[row]) - 1;
		y = FindMidH() + row;
		GotoXY(x, y);
		printf(" %s ", temp.c_str());
	}
}
void MenuGame::ClearGuide()
{
	 
	vector<string> str =Guide.Get();
	TextColor(15);
	GotoXY(0, 0);
	for (int row = 0; row  < Guide.Height(); row++)
	{
		string temp="";
		int sizes = str[row].length();
		for (int i = 0; i < sizes; i++)
			temp += " ";
		printf("%s\n", temp.c_str());
	}
}

void MenuGame::Write(ostream & out)
{
	out.write((char*)&_W, sizeof(_W));
	out.write((char*)&_H, sizeof(_H));
	Menucha.Write(out);
	Guide.Write(out);
	out.write((char*)&PastRow, sizeof(PastRow));
	out.write((char*)&CurrRow, sizeof(CurrRow));
}

void MenuGame::Read(istream & in)
{
	in.read((char*)&_W, sizeof(_W));
	in.read((char*)&_H, sizeof(_H));
	Menucha.Read(in);
	Guide.Read(in);
	in.read((char*)&PastRow, sizeof(PastRow));
	in.read((char*)&CurrRow, sizeof(CurrRow));
}
void MenuGame::Enter() 
{

}
void MenuGame::Control(char key)
{
	switch (key)
	{
	case'w':
	case UP:
		this->Up(); break;
	case DOWN:
	case's': this->Down(); break;
	case ENTER: this->Enter(); break;	 
	}
}