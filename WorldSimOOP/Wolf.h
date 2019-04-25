#pragma once
#include "Animal.h"


class Wolf : public Animal {
public:
	Wolf(int, int, World&);
	~Wolf();
	Organism* reproduce(int, int);
};