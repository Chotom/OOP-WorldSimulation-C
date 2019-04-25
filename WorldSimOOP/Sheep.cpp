#include "Sheep.h"

Sheep::Sheep(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 4;
	this->strength = 4;
	this->symbol = 's';
}

Sheep::~Sheep() {}

Organism* Sheep::reproduce(int posX, int posY) {
	return new Sheep(posX, posY, *world);
}
