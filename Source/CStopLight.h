#pragma once
#include "CGraphics.h"
#define RED_LIGHT_WAITING 4000		 
#define GREEN_LIGHT_WAITING 3000	 
#define TIME_BLINKING 2000				 
#define ONE_SECOND 1000	
class StopLight
{
private:
	int countDown;
	int countTime;
	bool isRed;
	bool warning, hidden;
	int delay;
	void SetTime(char);
public:
	StopLight();
	StopLight(char,bool );
	void Draw(int, int);
	void UpdateTime();
	void Animation(int, int);
	bool IsRed();
	~StopLight() {}
};

