#include "SosnowskyHogweed.h"

SosnowskyHogweed::SosnowskyHogweed(int posX, int posY, World& world) : Plant(posX, posY, world){
	this->strength = 10;
	this->canPoison = 1;
	this->symbol = 'x';
}

SosnowskyHogweed::~SosnowskyHogweed() {}

bool SosnowskyHogweed::action() {
	Organism* org = nullptr;

	if ((this->getPosX() - 1 >= 0) && ((world->getOrganism(this->getPosX() - 1, this->getPosY())) != nullptr)) {
		Organism* org = world->getOrganism(this->getPosX() - 1, this->getPosY());
		if (!dynamic_cast<Plant*>(org)) {
			world->setInformations(0, this, org);
			world->deleteOrganism(org);
		}
	}


	if ((this->getPosX() + 1 < world->getSizeX()) && ((world->getOrganism(this->getPosX() + 1, this->getPosY())) != nullptr)) {
		Organism* org = world->getOrganism(this->getPosX() + 1, this->getPosY());
		if (!dynamic_cast<Plant*>(org)) {
			world->setInformations(0, this, org);
			world->deleteOrganism(org);
		}
	}

	if ((this->getPosY() - 1 >= 0) && ((world->getOrganism(this->getPosX(), this->getPosY() - 1)) != nullptr)) {
		Organism* org = world->getOrganism(this->getPosX(), this->getPosY() - 1);
		if (!dynamic_cast<Plant*>(org)){
			world->setInformations(0, this, org);
			world->deleteOrganism(org);
		}
	}

	if ((this->getPosY() + 1 < world->getSizeY()) && ((world->getOrganism(this->getPosX(), this->getPosY() + 1)) != nullptr)) {
		Organism* org = world->getOrganism(this->getPosX(), this->getPosY() + 1);
		if (!dynamic_cast<Plant*>(org)) {
			world->setInformations(0, this, org);
			world->deleteOrganism(org);
		}
	}
	
	return Plant::action();
}

Organism* SosnowskyHogweed::reproduce(int posX, int posY) {
	return new SosnowskyHogweed(posX, posY, *world);
}
