#include "Dandelion.h"

Dandelion::Dandelion(int posX, int posY, World& world) : Plant(posX, posY, world) {
	this->symbol = '*';
}

Dandelion::~Dandelion() {}

bool Dandelion::action() {
	for (int i = 0; i < 3; i++) Plant::action();
	return false;
}

Organism* Dandelion::reproduce(int posX, int posY) {
	return new Dandelion(posX, posY, *world);
}
