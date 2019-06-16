#include "CAnimal.h"
Animal::Animal(){}
Animal::Animal(int x, int y):Object(x,y)
{
}
Animal::Animal(int x, int y, Direction dir) : Object(x, y, dir)
{
}
Animal::Animal(Direction dir) : Object(dir)
{
}
