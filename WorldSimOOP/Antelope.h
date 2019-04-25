#pragma once
#include "Animal.h"


class Antelope : public Animal {
public:
	Antelope(int, int, World&);
	~Antelope();
	bool action();
	Organism* reproduce(int, int);
};