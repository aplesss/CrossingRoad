#include "CStopLight.h"
StopLight::StopLight(){}
StopLight::StopLight(char sleep, bool redlight = false)
{
	countDown = redlight == false ? RED_LIGHT_WAITING : GREEN_LIGHT_WAITING;
	isRed = redlight;
	warning = false;
	countTime = 0;
	hidden = false;
	SetTime(sleep);
}
void StopLight::SetTime(char sleep)
{
	delay = sleep;
}
void StopLight::Draw(int x, int y)
{
	GotoXY(x, y);
	if (isRed  == true)
	{
		if (warning  == false)
			TextColor(BACKGROUND_LIGHTRED);
		else
		{
			if (hidden == true)
				TextColor(BACKGROUND_RED);
			else
				TextColor(BACKGROUND_LIGHTRED);
		}
		putchar(32);
	}
	else
	{
		if (warning == false)
			TextColor(BACKGROUND_LIGHTGREEN);
		else
		{
			if (hidden == true)
				TextColor(BACKGROUND_GREEN);
			else
				TextColor(BACKGROUND_LIGHTGREEN);
		}
		putchar(32);
	}
	TextColor(FOREGROUND_WHITE);
	GotoXY(x, y+1);
	cout << char(223);
}
void StopLight::UpdateTime()
{
	if (countTime == ONE_SECOND && countDown > TIME_BLINKING)
	{
		countDown -= countTime;
		countTime = 0;
	}

	if (countDown == TIME_BLINKING)
	{
		warning  = true;
		hidden= true;
	}
	if (countTime == ONE_SECOND / 2 && warning  == true)
	{
		countDown -= countTime;
		countTime = 0;
		hidden = !hidden;
	}
	if (countDown == 0)
	{
		countDown = isRed ? RED_LIGHT_WAITING : GREEN_LIGHT_WAITING;
		isRed  = !isRed;
		warning  = false;
	}
	countTime += delay;
}
void StopLight::Animation(int x, int y)
{
	while (1)
	{
		Draw(x, y);
		UpdateTime();
		Sleep(delay);
	}
}
bool StopLight::IsRed()
{
	return isRed;
}