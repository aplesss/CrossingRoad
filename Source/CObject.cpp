#pragma once
#include "CObject.h"
Object::Object()
{
	preX = -1;
}
Object::Object(Direction theDirec)
{
	dir = theDirec;
	preX = -1;
}
Object::Object(int x, int y, Direction theDirec)
{
	 X = x;
	 Y = y;
	dir = theDirec;
	preX = -1;
}
void Object::Music()
{
	const char* dirfile= GetSoundFileName();
	PlaySound(dirfile, NULL, SND_ASYNC);
}
void Object::Move()
{

		Character cha = GetCharacter();
		int width = cha.Width();
		COORD pos;
		if (dir == DLEFT) {
			if (X + width - 1 < BOARD_RIGHT_EDGE) {
				preX = X + width - 1;
			}

			if (X + width - 1 > BOARD_GAME_LEFT + 1) {	
				X--;
			}
			else {
				X = BOARD_GAME_RIGHT - width + 1;
			}
		}
		else {
			if (X > BOARD_LEFT_EDGE) {
				preX = X;
			}

			if (X < BOARD_GAME_RIGHT) {	
				X++;
			}
			else {
				X = BOARD_GAME_LEFT + 1;
			}
	}

}
void Object::Draw()
{
	
	switch (this->GetShape())
	{
	case DINOSAURS:
		TextColor(2);
		break;
	case CARS:
		TextColor(11);
		break;
	case BIRDS:
		TextColor(14);
		break;
	default:
		break;
	}
	Character cha = GetCharacter();
	int width = cha.Width();
	if (preX > 0 && preX != BOARD_GAME_RIGHT && preX != BOARD_GAME_LEFT) {
		ClearPre();
	}

	if (dir  == DLEFT) {

		if (X >= BOARD_GAME_RIGHT) {
			return;
		}
	}
	else if (dir == DRIGHT) {
		if (X + width - 1 < BOARD_GAME_LEFT) {
			return;
		}
		else if (X < BOARD_GAME_RIGHT && X + width - 1 > BOARD_GAME_RIGHT) {
			Object * newObj = this->Clone(BOARD_GAME_LEFT - (BOARD_GAME_RIGHT - X) + 1, Y);
			newObj->Draw();
			delete newObj;
		}
	}
	cha.Draw(X, Y);
	TextColor(7);
}

int Object::Width()
{
	Character cha = GetCharacter();
	return cha.Width();
}
int Object::Height()
{
	Character cha = GetCharacter();
	return cha.Height();
}
void Object::ClearPre()
{
	Character cha = GetCharacter();
	int height= cha.Height();
	for (int i = 0; i < height; i++) {
		GotoXY(preX, Y + i);
		//dung mutex dam bao thead
		lock_guard<mutex> lock(theLock);
		printf(" ");
	}
}
COORD Object::GetPos()
{
	COORD pos = { X,Y };
	return pos;
}
void Object::SetPos(int x, int y)
{
	X = x;
	Y = y;
}
void Object::Write(ostream &out)
{
	out.write((char*)&X, sizeof(X));
	out.write((char*)&Y, sizeof(Y));
	out.write((char*)&preX, sizeof(preX));
	out.write((char*)&dir, sizeof(dir));
}
void Object::Read(istream &in)
{
	in.read((char*)&X, sizeof(X));
	in.read((char*)&Y, sizeof(Y));
	in.read((char*)&preX, sizeof(preX));
	in.read((char*)&dir, sizeof(dir));
}

