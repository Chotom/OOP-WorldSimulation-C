#pragma once
#include "Animal.h"


class Turtle : public Animal {
public:
	Turtle(int, int, World&);
	Turtle(int, int, World&, int);
	~Turtle();
	bool action();
	Organism* reproduce(int, int);
};