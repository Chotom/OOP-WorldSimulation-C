#include "Antelope.h"

Antelope::Antelope(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 4;
	this->strength = 4;
	this->symbol = 'a';
	this->canEscape = 1;
}

Antelope::Antelope(int posX, int posY, World& world, int strength) : Animal(posX, posY, world, strength) {
	this->initiative = 4;
	this->symbol = 'A';
	this->canEscape = 1;
}

Antelope::~Antelope() {}

bool Antelope::action() {
	int walkBoostChange = rand() % 2;
	if (walkBoostChange) setWalkBoost(1);
	else setWalkBoost(0);

	return Animal::action();
}

Organism* Antelope::reproduce(int posX, int posY)
{
	return new Antelope(posX, posY, *world);
}
