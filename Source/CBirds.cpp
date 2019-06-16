#pragma once
#include "CBirds.h"
const char* Birds::fileName= "Sound\\Bird.wav";
Character Birds::cLeft("Character\\Bird_Left.txt");
Character Birds::cRight("Character\\Bird_Right.txt");
Birds::Birds() {}
Birds::Birds(Direction theDirec) : Animal(theDirec) {}
Birds::Birds(int x, int y) : Animal(x, y) {}
Birds::Birds(int x, int y, Direction theDirec) : Animal(x, y, theDirec) {}
const Character & Birds::GetCharacter()
{
	if (dir  == DRIGHT) {
		return cRight;
	}
	else {
		return cLeft;
	}
}
const char * Birds::GetSoundFileName()
{
	return fileName;
}
Object * Birds::Clone(int x, int y)
{
	return new Birds(x, y, dir);
}
Objects Birds::GetShape()
{
	return BIRDS;
}