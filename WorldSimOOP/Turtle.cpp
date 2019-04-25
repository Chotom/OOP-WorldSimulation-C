#include "Turtle.h"

Turtle::Turtle(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 1;
	this->strength = 2;
	this->symbol = 't';
	this->canDef = 1;
}

Turtle::~Turtle() {}

bool Turtle::action() {
	int canMove = rand() % 4;
	if (canMove == 0) return Animal::action();
	else return false;
}

Organism* Turtle::reproduce(int posX, int posY) {
	return new Turtle(posX, posY, *world);
}
