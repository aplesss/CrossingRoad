#pragma once
#include"CCharacter.h"
#include"CGraphics.h"
class People
{
private:
	int X, Y;
	void Up();
	void Left();
	void Right();
	void Down();
	bool Live;
	static Character cha;
	vector<COORD> oldPos;
	void ClearPre();
public:
	People(int, int);
	Character& GetCharacter();
	int Width();
	int Height();
	void SetLive(bool);
	void Write(ostream&);
	void Read(istream&);
	void Move(char);
	bool IsDied();
	void Draw(bool color=true);
	COORD GetPos();
	People();
	~People();
};

