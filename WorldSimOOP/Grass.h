#pragma once
#include "Plant.h"


class Grass : public Plant {
public:
	Grass(int, int, World&);
	~Grass();

	Organism* reproduce(int, int);
};