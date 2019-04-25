#include "Wolf.h"

Wolf::Wolf(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 5;
	this->strength = 9;
	this->symbol = 'w';
}

Wolf::~Wolf() {}

Organism* Wolf::reproduce(int posX, int posY) {
	return new Wolf(posX, posY, *world);
}
