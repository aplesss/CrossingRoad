#pragma once
#include"CVehicals.h"
class Trucks : public Vehicals
{
private:
	static const char *fileName;
	static Character cLeft, cRight;
public:
	Trucks();
	Trucks(Direction);
	Trucks(int, int, Direction);
	const Character& GetCharacter() override;
	const char * GetSoundFileName() override;
	Object * Clone(int, int) override;
	Objects GetShape() override;
};

