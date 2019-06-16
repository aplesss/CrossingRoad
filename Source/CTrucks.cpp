#include "CTrucks.h"
const char* Trucks::fileName = "Sound\\Truck.wav";
Character Trucks::cLeft("Character\\Truck_Left.txt");
Character Trucks::cRight("Character\\Truck_Right.txt");

Trucks::Trucks() {}

Trucks::Trucks(Direction theDirec) : Vehicals(theDirec) {}

Trucks::Trucks(int x, int y, Direction theDirec) : Vehicals(x, y, theDirec) {}
const Character & Trucks::GetCharacter()
{
	if (dir == DRIGHT) {
		return cRight;
	}
	else {
		return cLeft;
	}
}

const char * Trucks::GetSoundFileName()
{
	return fileName;
}

Object * Trucks::Clone(int x, int y)
{
	return new Trucks(x, y, dir);
}

Objects Trucks::GetShape()
{
	return	TRUCKS;
}

