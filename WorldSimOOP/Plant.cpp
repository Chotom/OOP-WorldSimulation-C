#include "Plant.h"

Plant::Plant(int posX, int posY, World& world) : Organism(posX, posY, world) {
	initiative = 0;
	symbol = 'p';
}

Plant::~Plant() {}

bool Plant::action() {
	int canStart = rand() % 10;
	if (canStart == 0) {
		bool possiblePlant[4] = { 0,0,0,0 };
		bool freePossition = 0;
		int plantX = 0, plantY = 0;
		//fiding place to seed
		if ((this->getPosX() - 1 >= 0) && ((world->getOrganism(this->getPosX() - 1, this->getPosY()) == nullptr)))
			possiblePlant[0] = 1, freePossition = 1;
		if ((this->getPosX() + 1 < world->getSizeX()) && ((world->getOrganism(this->getPosX() + 1, this->getPosY()) == nullptr)))
			possiblePlant[1] = 1, freePossition = 1;
		if ((this->getPosY() - 1 >= 0) && ((world->getOrganism(this->getPosX(), this->getPosY() - 1) == nullptr)))
			possiblePlant[2] = 1, freePossition = 1;
		if ((this->getPosY() + 1 < world->getSizeY()) && ((world->getOrganism(this->getPosX(), this->getPosY() + 1) == nullptr)))
			possiblePlant[3] = 1, freePossition = 1;

		if (!freePossition) return false;

		while (true) {
			int seed = rand() % 4;
			if (possiblePlant[seed]) {
				if (seed == 0) plantX--;
				else if (seed == 1) plantX++;
				else if (seed == 2) plantY--;
				else if (seed == 3) plantY++;
				break;
			}
			else continue;
		}
		//add seed to world
		world->addOrganism(this->reproduce((this->getPosX() + plantX), (this->getPosY() + plantY)));
	}
	
	return false;
}
