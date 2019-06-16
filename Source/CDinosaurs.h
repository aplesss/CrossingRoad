#pragma once
#include"CAnimal.h"
class Dinosaurs:public Animal
{
private:
	static const char* fileName;
	static Character cLeft, cRight;
public:
	Dinosaurs();
	Dinosaurs(int, int);
	Dinosaurs(int, int, Direction);
	Dinosaurs(Direction);
	const Character& GetCharacter() override;
	const char* GetSoundFileName() override;
	Object *Clone(int, int) override;
	Objects GetShape() override;
	~Dinosaurs() {}
};

