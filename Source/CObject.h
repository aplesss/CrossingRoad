#pragma once
#include"CCharacter.h"
#include<functional>
#include<mutex>
#include"CPeople.h"
#pragma comment(lib, "Winmm.lib")
enum Direction {
	DLEFT, DRIGHT
};

enum Objects {
	BIRDS, CARS, DINOSAURS, TRUCKS
};
class Line;
class Object abstract
{
	friend class Line;
private:
	int X, Y;
protected:
	int preX;
	Direction dir;
public:
	Object();
	Object(Direction);
	Object(int, int, Direction dirs = DLEFT);
	void Music();
	int Width();
	int Height();
	void ClearPre();
	void Draw();
	COORD GetPos();
	void SetPos(int, int);
	void Write(ostream &);
	void Read(istream &);
	void Move();
	virtual const char* GetSoundFileName() = 0;
	virtual const Character& GetCharacter() = 0;
	virtual Object *Clone(int, int)=0;
	virtual Objects GetShape()  = 0;
	~Object() {}
};

