#pragma once
#include "Plant.h"


class Guarana : public Plant {
public:
	Guarana(int, int, World&);
	~Guarana();

	Organism* reproduce(int, int);
};