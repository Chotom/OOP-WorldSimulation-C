#pragma once
#include "Organism.h"


class Plant : public Organism {
public:
	Plant(int, int, World&);
	~Plant();
	virtual bool action();
};