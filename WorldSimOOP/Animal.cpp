#include "Animal.h"

Animal::Animal(int posX, int posY, World &world) : Organism(posX, posY, world) {
	this->initiative = 1;
	this->strength = 1;
	this->symbol = '@';
	this->walkBoost = 0;
}

Animal::Animal(int posX, int posY, World& world, int strength) : Organism(posX, posY, world, strength) {
	this->initiative = 1;
	this->symbol = '@';
	this->walkBoost = 0;
}

bool Animal::action() {
	//randomise walking
	int walkRange = 1;
	if (walkBoost) walkRange = 2;
	int changeX = 0;
	int changeY = 0;
	int motion = rand() % 4;
	switch (motion) {
	case 0:
		changeX-=walkRange;
		if ((changeX + this->getPosX()) < 0) changeX *= -1;
		break;
	case 1:
		changeX+=walkRange;
		if ((changeX + this->getPosX()) >= world->getSizeX()) changeX *= -1;
		break;
	case 2:
		changeY-=walkRange;
		if ((changeY + this->getPosY()) < 0) changeY *= -1;
		break;
	case 3:
		changeY+=walkRange;
		if ((changeY + this->getPosY()) >= world->getSizeY()) changeY *= -1;
		break;
	}
	Organism* enemy = world->getOrganism(this->getPosX() + changeX, this->getPosY() + changeY);
	if (enemy != nullptr) return enemy->collision(this, changeX, changeY);
		
	world->deletePosition(this);
	this->posX += changeX;
	this->posY += changeY;
	world->setPosition(this);

	return false;
}

bool Animal::collision(Organism* org, int changeX, int changeY) {
	//Animal copulate when find type
	if (Animal * a = dynamic_cast<Animal*>(org)) {
		if (this->getSymbol() == org->getSymbol() && (this->getReproduce()) && (a->getReproduce())) {
			bool possibleBorn[4] = { 0,0,0,0 };
			bool freePossition = 0;
			int bornX = 0, bornY = 0;
			//fiding place to born
			if ((org->getPosX() - 1 >= 0) && ((world->getOrganism(org->getPosX() - 1, org->getPosY()) == nullptr)))
				possibleBorn[0] = 1, freePossition = 1;
			if ((org->getPosX() + 1 < world->getSizeX()) && ((world->getOrganism(org->getPosX() + 1, org->getPosY()) == nullptr)))
				possibleBorn[1] = 1, freePossition = 1;
			if ((org->getPosY() - 1 >= 0) && ((world->getOrganism(org->getPosX(), org->getPosY() - 1) == nullptr)))
				possibleBorn[2] = 1, freePossition = 1;
			if ((org->getPosY() + 1 < world->getSizeY()) && ((world->getOrganism(org->getPosX(), org->getPosY() + 1) == nullptr)))
				possibleBorn[3] = 1, freePossition = 1;

			if (!freePossition) return false;

			while (true) {
				int move = rand() % 4;
				if (possibleBorn[move]) {
					if (move == 0) bornX--;
					else if (move == 1) bornX++;
					else if (move == 2) bornY--;
					else if (move == 3) bornY++;
					break;
				}
				else continue;
			}
			//add baby to world and end adults turns
			world->addOrganism(org->reproduce((org->getPosX() + bornX), (org->getPosY() + bornY)));
			world->setInformations(1, world->getOrganism(org->getPosX() + bornX, org->getPosY() + bornY), nullptr);
			this->setReproduce(0);
			a->setReproduce(0);
			return false;
		}
		//Adult cant copulate with child
		else if (this->getSymbol() == org->getSymbol() - 'A' + 'a') return false;
		//Adult cant copulate twice in one turn
		else if (this->getSymbol() == org->getSymbol()) return false;
	}
	return Organism::collision(org, changeX, changeY);
}



void Animal::setWalkBoost(bool change) {
	this->walkBoost = change;
}

bool Animal::getWalkBoost() {
	return walkBoost;
}

Animal::~Animal() {}