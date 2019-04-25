#include "Guarana.h"

Guarana::Guarana(int posX, int posY, World& world) : Plant(posX, posY, world) {
	this->symbol = 'g';
	this->boost = 3;
}

Guarana::~Guarana() {}

Organism* Guarana::reproduce(int posX, int posY)
{
	return new Guarana(posX, posY, *world);
}
