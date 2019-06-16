#pragma once
#include "CDinosaurs.h"
const char* Dinosaurs::fileName = "Sound\\Dinosaur.wav";
Character Dinosaurs::cLeft("Character\\Dinosaur_Left.txt");
Character Dinosaurs::cRight("Character\\Dinosaur_Right.txt");
Dinosaurs::Dinosaurs() {}

Dinosaurs::Dinosaurs(Direction theDirec) : Animal(theDirec) {}

Dinosaurs::Dinosaurs(int x, int y) : Animal(x, y) {}

Dinosaurs::Dinosaurs(int x, int y, Direction theDirec) : Animal(x, y, theDirec) {}

const Character & Dinosaurs::GetCharacter()
{
	if (dir==DRIGHT) {
		return cRight;
	}
	else {
		return cLeft;
	}
}
const char * Dinosaurs::GetSoundFileName()
{
	return fileName;
}

Object * Dinosaurs::Clone(int x, int y)
{
	return new Dinosaurs(x, y, dir);
}

Objects Dinosaurs::GetShape()
{
	return DINOSAURS;
}