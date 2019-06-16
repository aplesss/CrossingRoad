#pragma once
#include"CObject.h"
class Animal abstract : public Object
{
public:
	Animal();
	Animal(Direction);
	Animal(int, int);
	Animal(int, int, Direction);
};