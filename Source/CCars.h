#pragma once
#include"CVehicals.h"
class Cars : public Vehicals
{
private:
	static const char *fileName;
	static Character cLeft, cRight;
public:
	Cars();
	Cars(Direction);
	Cars(int, int, Direction);
	const Character& GetCharacter() override;
	const char * GetSoundFileName() override;
	Object * Clone(int, int) override;
	Objects GetShape() override;
};