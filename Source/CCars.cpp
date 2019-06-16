#pragma once
#include "CCars.h"
const char* Cars::fileName = "Sound\\Car.wav";
Character Cars::cLeft("Character\\Car_Left.txt");
Character Cars::cRight("Character\\Car_Right.txt");
Cars::Cars() {}
Cars::Cars(Direction theDirec) : Vehicals(theDirec) {}
Cars::Cars(int x, int y, Direction theDirec) : Vehicals(x, y, theDirec) {}
const Character & Cars::GetCharacter()
{
	if (dir == DRIGHT) {
		return cRight;
	}
	else {
		return cLeft;
	}
}
const char * Cars::GetSoundFileName()
{
	return fileName;
}
Object * Cars::Clone(int x, int y)
{
	return new Cars(x, y, dir);
}
Objects Cars::GetShape()
{
	return	CARS;
}