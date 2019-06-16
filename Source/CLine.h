#pragma once
#include"CObject.h"
#include"CPeople.h"
#include"CBirds.h"
#include"CDinosaurs.h"
#include"CTrucks.h"
#include"CStopLight.h"
#include"CCars.h"
class Line
{
public:
	int width, height;
	COORD pos;
	vector<Object*> obj;
	StopLight *stop;
	Direction dir;
	short sleep;
	short timeCount;
	short soundWaiting;
public:
	Line();
	Line(COORD, vector<Object*>, Direction, short, short);
	~Line() {}
	int Height();
	void PosUpdate();
	void Draw();
	void Music(const People&);
	COORD GetPos();
	bool IsImpact(People& people);
	void Write(ostream& outDev);
	void Read(istream& inDev);
	void Located();
	bool IsInside(const People &);
};

