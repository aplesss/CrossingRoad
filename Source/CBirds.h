#pragma once
#include "CAnimal.h"
class Birds: public Animal
{
private:
	static const char* fileName;
	static Character cLeft, cRight;
public:
	Birds();
	Birds(int, int);
	Birds(int, int,Direction);
	Birds(Direction);
	const Character& GetCharacter() override;
	const char* GetSoundFileName() override;
	Object *Clone(int, int) override;
	Objects GetShape() override;
	~Birds(){}
};