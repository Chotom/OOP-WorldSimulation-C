#pragma once
#include "Plant.h"


class DeadlyNightshade : public Plant {
public:
	DeadlyNightshade(int, int, World&);
	~DeadlyNightshade();

	Organism* reproduce(int, int);
};