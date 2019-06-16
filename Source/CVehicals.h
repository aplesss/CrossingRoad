#pragma once
#include"CObject.h"
class Vehicals : public Object
{
public:
	Vehicals();
	Vehicals(Direction);
	Vehicals(int, int);
	Vehicals(int, int, Direction);
};

