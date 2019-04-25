#include <iostream>
#include "Organism.h"

Organism::Organism() {}

Organism::Organism(int posX, int posY, World &world) {
	this->posX = posX;
	this->posY = posY;
	this->world = &world;
	this->initiative = 0;
	this->strength = 0;
	this->symbol = '.';
	this->boost = 0;
	this->canEscape = 0;
	this->canDef = 0;
	this->canPoison = 0;
	this->canReproduce = 0;
}

Organism::Organism(int posX, int posY, World& world, int strength) {
	this->posX = posX;
	this->posY = posY;
	this->world = &world;
	this->initiative = 0;
	this->strength = strength;
	this->symbol = '.';
	this->boost = 0;
	this->canEscape = 0;
	this->canDef = 0;
	this->canPoison = 0;
	this->canReproduce = 1;
}


//return false - attacker alive
bool Organism::collision(Organism* org, int changeX, int changeY) {

	//both alive nothing change
	if (this->getDefence() && (org->getStrength() < 5)) {
		world->setInformations(6, org, this);
		return false;
	}

	//defender die and give boost to attacker
	else if (this->getBoost()) {
		world->setInformations(7, org, this);
		org->setStrength(this->boost);
		
		world->deletePosition(org);
		org->posX += changeX;
		org->posY += changeY;
		world->setPosition(org);

		world->deleteOrganism(this);
		return false;
	}

	//both die
	else if (this->getPoison()) {
		world->setInformations(0, this, org);
		world->setInformations(0, org, this);

		world->deleteOrganism(this);
		return true;	
	}

	//defender die or espace
	else if (this->getStrength() <= org->getStrength()) {
		int escape = rand() % 2;
		if (escape * this->canEscape == 1) {
			//check any possible way to escape
			if (randomiseEscape(this, this->getPosX(), this->getPosY())) {
				world->setInformations(5, org, this);

				world->deletePosition(org);
				org->posX += changeX;
				org->posY += changeY;
				world->setPosition(org);
				return false;
			}
			//defender die
			else {
				world->setInformations(0, org, this);

				world->deletePosition(org);
				org->posX += changeX;
				org->posY += changeY;
				world->setPosition(org);
				world->deleteOrganism(this);
				return false;
			}
		}
		//defender die
		else {
			world->setInformations(0, org, this);

			world->deletePosition(org);
			org->posX += changeX;
			org->posY += changeY;
			world->setPosition(org);

			world->deleteOrganism(this);
		}
		return false;
	}
	//attacker die
	else {
		world->setInformations(0, this, org);
		return true;
	}
}
bool Organism::randomiseEscape(Organism* org, int posX, int posY) {
	bool possibleMove[4] = { 0,0,0,0 };
	bool freePossition = 0;
	//check all possible ways to go
	if ((posX - 1 >= 0) && (world->getOrganism(posX - 1, posY) == nullptr)) possibleMove[0] = 1, freePossition = 1;
	if ((posX + 1 < world->getSizeX()) && (world->getOrganism(posX + 1, posY) == nullptr)) possibleMove[1] = 1, freePossition = 1;
	if ((posY - 1 >= 0) && (world->getOrganism(posX, posY - 1) == nullptr)) possibleMove[2] = 1, freePossition = 1;
	if ((posY + 1 < world->getSizeY()) && (world->getOrganism(posX, posY + 1) == nullptr)) possibleMove[3] = 1, freePossition = 1;

	if (!freePossition) return false;

	//find proper way
	while (true) {
		int changeX = 0, changeY = 0;
		int move = rand() % 4;
		if (possibleMove[move]) {
			if (move == 0) changeX--;
			else if (move == 1) changeX++;
			else if (move == 2) changeY--;
			else if (move == 3) changeY++;

			world->deletePosition(this);
			this->posX += changeX;
			this->posY += changeY;
			world->setPosition(this);

			return true;
		}
		else continue;
	}
}

void Organism::setStrength(int s) {
	this->strength += s;
}
void Organism::setReproduce(bool change) {
	this->canReproduce = change;
}
void Organism::setSymbol() {
	if(this->getSymbol() <= 'z' && this->getSymbol() >= 'a')
		this->symbol = symbol - 'a' + 'A';
}
void Organism::drawSymbol() {
	std::cout << getSymbol();
}

int Organism::getPosX() {
	return posX;
}
int Organism::getPosY() {
	return posY;
}
int Organism::getStrength() {
	return strength;
}
int Organism::getInitiative() {
	return initiative;
}
char Organism::getSymbol() {
	return this->symbol;
}
bool Organism::getPoison() {
	return this->canPoison;
}
bool Organism::getReproduce() {
	return canReproduce;
}
bool Organism::getBoost() {
	if (this->boost == 0) return false;
	else return true;
}
bool Organism::getDefence() {
	return this->canDef;
}

Organism::~Organism() {}