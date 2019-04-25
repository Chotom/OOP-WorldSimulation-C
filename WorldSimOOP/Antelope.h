#pragma once
#include "Animal.h"


class Antelope : public Animal {
public:
	Antelope(int, int, World&);
	Antelope(int, int, World&, int);
	~Antelope();
	bool action();
	Organism* reproduce(int, int);
};