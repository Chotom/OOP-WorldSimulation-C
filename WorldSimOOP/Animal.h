#pragma once
#include "Organism.h"

class Animal : public Organism {
protected:
	bool walkBoost;
public:
	Animal(int, int, World&);
	Animal(int, int, World&, int);
	~Animal();
	virtual bool collision(Organism*, int, int);
	virtual bool action();

	bool getWalkBoost();
	void setWalkBoost(bool);
};