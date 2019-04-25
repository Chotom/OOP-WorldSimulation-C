#include "Fox.h"

Fox::Fox(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 7;
	this->strength = 3;
	this->symbol = 'f';
}

Fox::Fox(int posX, int posY, World& world, int strength) : Animal(posX, posY, world, strength) {
	this->initiative = 7;
	this->symbol = 'F';
}

Fox::~Fox() {}

bool Fox::action() {
	bool possibleMove[4] = { 0,0,0,0 };
	bool freePossition = 0;
	int changeX = 0, changeY = 0;

	if ((posX - 1 >= 0) && ((world->getOrganism(posX - 1, posY) == nullptr) || (world->getOrganism(posX - 1, posY)->getStrength() < this->getStrength())))
		possibleMove[0] = 1, freePossition = 1;
	if ((posX + 1 < world->getSizeX()) && ((world->getOrganism(posX + 1, posY) == nullptr) || (world->getOrganism(posX + 1, posY)->getStrength() < this->getStrength())))
		possibleMove[1] = 1, freePossition = 1;
	if ((posY - 1 >= 0) && ((world->getOrganism(posX, posY - 1) == nullptr) || (world->getOrganism(posX, posY - 1)->getStrength() < this->getStrength())))
		possibleMove[2] = 1, freePossition = 1;
	if ((posY + 1 < world->getSizeY()) && ((world->getOrganism(posX, posY + 1) == nullptr) || (world->getOrganism(posX, posY + 1)->getStrength() < this->getStrength())))
		possibleMove[3] = 1, freePossition = 1;

	if (!freePossition) return false;

	while (true) {	
		int move = rand() % 4;
		if (possibleMove[move]) {
			if (move == 0) changeX--;
			else if (move == 1) changeX++;
			else if (move == 2) changeY--;
			else if (move == 3) changeY++;
			break;
		}
		else continue;
	}

	Organism* enemy = world->getOrganism(getPosX() + changeX, getPosY() + changeY);
	if (enemy != nullptr) return enemy->collision(this, changeX, changeY);

	world->deletePosition(this);
	posX += changeX;
	posY += changeY;
	world->setPosition(this);

	return false;

}

Organism* Fox::reproduce(int posX, int posY) {
	return new Fox(posX, posY, *world);
}
