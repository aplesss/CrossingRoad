#include "CVehicals.h"
Vehicals::Vehicals() {}
Vehicals::Vehicals(Direction theDirec) : Object(theDirec) {}
Vehicals::Vehicals(int x, int y) : Object(x, y) {}
Vehicals::Vehicals(int x, int y, Direction theDirec) :Object(x, y, theDirec) {}
