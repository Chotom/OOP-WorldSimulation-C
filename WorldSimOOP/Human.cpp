#include "Human.h"

Human::Human(int posX, int posY, World& world) : Animal(posX, posY, world) {
	this->initiative = 4;
	this->strength = 5;
	this->symbol = 'H';
	this->canReproduce = 1;
	this->cooldown = 0;
}

Human::Human(int posX, int posY, World& world, int strength, int cooldown) : Animal(posX, posY, world, strength) {
	this->initiative = 4;
	this->symbol = 'H';
	this->cooldown = cooldown;
}

Human::~Human() {}

bool Human::action() {
	if (cooldown > 7) {
		this->setWalkBoost(1);
	}
	else if (cooldown > 5) {
		int walkBoostChange = rand() % 2;
		if (walkBoostChange) setWalkBoost(1);
	}

	int walkRange = 1;
	if (walkBoost) walkRange = 2;
	setWalkBoost(0);
	int changeX = 0;
	int changeY = 0;
	char zn = world->getZn();

	if(zn == 'r' && cooldown == 0){
		setSuperAbility();
		world->setInformations(9, this, nullptr);
	}

	else {
		switch (zn) {
		case 'w':
			changeX -= walkRange;
			if ((changeX + this->getPosX()) < 0) changeX = 0;
			break;
		case 's':
			changeX += walkRange;
			if ((changeX + this->getPosX()) >= world->getSizeX()) changeX = 0;
			break;
		case 'a':
			changeY -= walkRange;
			if ((changeY + this->getPosY()) < 0) changeY = 0;
			break;
		case 'd':
			changeY += walkRange;
			if ((changeY + this->getPosY()) >= world->getSizeY()) changeY = 0;
			break;
		}
		if (changeX != 0 || changeY != 0) {
			Organism* enemy = world->getOrganism(this->getPosX() + changeX, this->getPosY() + changeY);

			if (enemy != nullptr) 
				return enemy->collision(this, changeX, changeY);

			world->deletePosition(this);
			posX += changeX;
			posY += changeY;
			world->setPosition(this);
		}
	}

	if(this->cooldown > 0)this->cooldown--;

	return false;
}

void Human::setSuperAbility() {
	this->cooldown = 10;
}

int Human::getCooldown() {
	return this->cooldown;
}

Organism* Human::reproduce(int, int) {
	return nullptr;
}
