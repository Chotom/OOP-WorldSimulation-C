#pragma once
#include "Animal.h"


class Turtle : public Animal {
public:
	Turtle(int, int, World&);
	~Turtle();
	bool action();
	Organism* reproduce(int, int);
};