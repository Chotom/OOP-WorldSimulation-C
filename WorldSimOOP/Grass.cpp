#include "Grass.h"

Grass::Grass(int posX, int posY, World& world) : Plant(posX, posY, world) { 
	this->symbol = '|';
}

Grass::~Grass() {}

Organism* Grass::reproduce(int posX, int posY) {
	return new Grass(posX, posY, *world);
}
