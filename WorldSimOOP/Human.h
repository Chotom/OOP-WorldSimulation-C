#pragma once
#include "Animal.h"

class Human : public Animal {
	int turnLeft, cooldown;
	bool superAbility;
public:
	Human(int, int, World&);
	~Human();
	bool action();
	void setSuperAbility();
	Organism* reproduce(int, int);
};