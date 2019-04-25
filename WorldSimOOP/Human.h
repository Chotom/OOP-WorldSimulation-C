#pragma once
#include "Animal.h"

class Human : public Animal {
	int cooldown;
public:
	Human(int, int, World&);
	Human(int, int, World&, int, int);
	~Human();
	bool action();
	void setSuperAbility();
	int getCooldown();
	Organism* reproduce(int, int);
};