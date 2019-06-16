#pragma once
#include"CCharacter.h"
#include<conio.h>
#include<time.h>
class MenuGame
{
private:
	int _W;
	int _H;
	Character Menucha;
	Character Guide;
	int PastRow;
	int CurrRow;
	int FindMidH();
	int FindMidW(string);
	int FindLongestPos(vector<string>);
	void Up();
	void Down();
	void Enter();
public:
	MenuGame();
	MenuGame(int, int);
	~MenuGame();
	void Clear();
	void SetMenu(const char*);
	void Control(char);
	string Slection(bool sound=true);
	void Draw();
	void DrawGuide();
	void ClearMenu();
	void ClearGuide();
	void Write(ostream &);
	void Read(istream &);
};

