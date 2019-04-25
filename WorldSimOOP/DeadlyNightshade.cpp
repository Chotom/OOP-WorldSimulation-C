#include "DeadlyNightshade.h"

DeadlyNightshade::DeadlyNightshade(int posX, int posY, World& world) : Plant(posX, posY, world) {
	this->symbol = 'd';
	this->strength = 99;
	this->canPoison = 1;
}

DeadlyNightshade::~DeadlyNightshade() {}

Organism* DeadlyNightshade::reproduce(int posX, int posY) {
	return new DeadlyNightshade(posX, posY, *world);
}
