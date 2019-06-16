#pragma once
#include "CPeople.h"
Character People::cha("Character\\People.txt");
People::People() {}
People::~People() {}
People::People(int x, int y)
{
	X = x;
	Y = y;
	COORD temp = { -1,-1 };
	oldPos.push_back(temp);
	oldPos.resize(3);
}
void People::Up()
{
	int width = this->Width();
	int height = this->Height();
	oldPos.clear();
	COORD pos = { 0, Y + height - 1 };
	for (int i = 0; i < width; i++) {
		pos.X = X + i;
		pos.Y = Y + height - 1;
		oldPos.push_back(pos);
	}

	if (Y > BOARD_GAME_TOP + 1) {
		Y--;
	}
}
void People::Left()
{
	int width = this->Width();
	int height = this->Height();
	oldPos.clear();
	COORD pos = { X + width - 1 ,0};
	for (int i = 0; i < height; i++) {
		pos.Y =  Y + i;
		oldPos.push_back(pos);
	}

	if (X > BOARD_GAME_LEFT + 1) {
		 X--;
	}
	
}
void People::Right()
{
	int width = this->Width();
	int height = this->Height();
	oldPos.clear();
	COORD pos = { X };
	for (int i = 0; i < height; i++) {
		pos.Y = Y + i;
		oldPos.push_back(pos);
	}
	if (X + cha.Width() - 1 < BOARD_GAME_RIGHT - 1) {
		X++;
	}
}
void People::Down()
{
	int width = this->Width();
	int height = this->Height();
	oldPos.clear();
	COORD pos = { 0,  Y };

	for (int i = 0; i < width; i++) {
		pos.X =  X + i;
		oldPos.push_back(pos);
	}

	if (Y + cha.Height() - 1 < BOARD_GAME_BOTTOM - 1) {
		Y++;
	}
}
void People::Move(char key)
{
	if (key == LEFT || key == 'a' ) {
		this->Left();
	}
	else if (key==RIGHT|| key == 'd' ) {
		this->Right();
	}
	else if (key==DOWN||key == 's') {
		this->Down();
	}
	else if (key==UP||key == 'w') {
		this->Up();
	}
}

bool People::IsDied()
{
	return Live == false;
}

void People::Draw(bool color)
{
	if (oldPos[0].X > 0) {
		this->ClearPre();
	}
	if(color) TextColor(6);
	cha.Draw(X, Y);
	TextColor(7);

}

void People::ClearPre()
{
	int len = oldPos.size();

	for (int i = 0; i < len; i++) {
		GotoXY(oldPos[i]);
		lock_guard<mutex> lock(theLock);
		cout<<" ";
	}
}

COORD People::GetPos()
{
	COORD pos = { X,Y };
	return pos;
}

Character& People::GetCharacter()
{
	return cha;
}

int People::Width()
{
	if (cha.width == 0) {
		Character f("Character\\people.txt");
		return f.Width();
	}
	return cha.Width();
}

int People::Height()
{
	if (cha.height == 0) {
		Character f("Character\\people.txt");
		return f.Height();
	}
	return cha.Height();
}

void People::SetLive(bool live)
{
	Live = live;
}

void People::Write(ostream& outDev)
{
	outDev.write((char*)&X, sizeof(X));
	outDev.write((char*)&Y, sizeof(Y));
	outDev.write((char*)&Live, sizeof(Live));
	int num = oldPos.size();
	outDev.write((char*)&num, sizeof(num));
	outDev.write((char*)&oldPos[0], num * sizeof(oldPos[0]));
}

void People::Read(istream& inDev)
{
	inDev.read((char*)&X, sizeof(X));
	inDev.read((char*)&Y, sizeof(Y));
	inDev.read((char*)&Live, sizeof(Live));
	int num;
	inDev.read((char*)&num, sizeof(num));
	oldPos.resize(num);
	inDev.read((char*)&oldPos[0], num * sizeof(COORD));
}

