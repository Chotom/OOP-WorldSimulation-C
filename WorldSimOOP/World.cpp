#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Antelope.h"
#include "Fox.h"
#include "Plant.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"
#include "Dandelion.h"
#include "DeadlyNightshade.h"
#include "SosnowskyHogweed.h"
#include "Grass.h"
#include "Guarana.h"
#include "Plant.h"
#include "Human.h"

using namespace std;

World::World(int sizeX, int sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->map = new Organism**[sizeX];
	this->turn = 0;
	this->zn = 0;
	this->information = "";
	//fill map with empty organisms
	for (int i = 0; i < sizeX; i++) map[i] = new Organism*[sizeY]();
	
	//adding organisms to world
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			
		}
	}
	addOrganism(new Turtle(0, 0, *this));
	//addOrganism(new Turtle(1, 3, *this));
	//addOrganism(new Turtle(1, 1, *this));
	//addOrganism(new Turtle(0, 3, *this));
	addOrganism(new Antelope(1, 5, *this));
	//addOrganism(new Antelope(2, 5, *this));
	//addOrganism(new Antelope(5, 5, *this));
	//addOrganism(new Antelope(1, 2, *this));
	addOrganism(new Guarana(2, 2, *this));
	addOrganism(new Dandelion(4, 4, *this));
	addOrganism(new Human(1, 1, *this));
	addOrganism(new SosnowskyHogweed(4, 5, *this));
	addOrganism(new Wolf(3, 3, *this));
	//addOrganism(new Wolf(3, 2, *this));
	//addOrganism(new Fox(2, 3, *this));
	//addOrganism(new Fox(4, 3, *this));
	addOrganism(new Fox(2, 3, *this));
}

void World::startGame() {
	drawWorld();
	while(zn != 27) {
		setNextTurn();
	}
}
void World::setNextTurn() {
	this->turn++;

	// do action of every organism on the list
	list<Organism*>::iterator it = initiativeList.begin();
	while (it != initiativeList.end()) {

		zn = _getch();

		if (zn == 27) break;
		if (zn != 32) continue;

		setInformations(10, (*it), nullptr);
		//when organism is new born now he become adult
		if (!(*it)->getReproduce()) {
			if (!((*it)->getSymbol() <= 'Z' && (*it)->getSymbol() >= 'A')) {
				setInformations(2, (*it), nullptr);
				(*it)->setSymbol();
			}
			else setInformations(4, (*it), nullptr);
			it++;
		}
		//get zn to walk as human
		else if (dynamic_cast<Human*> (*it)) {
			setInformations(8, (*it), nullptr);
			drawWorld();
			cout << information;

			while ((zn != 'w') && (zn != 's') && (zn != 'a') && (zn != 'd') && (zn != 'r')) {
				zn = _getch();
			}

			if ((*it)->action()) {
				deletePosition(*it);
				delete* it;
				it = initiativeList.erase(find(initiativeList.begin(), initiativeList.end(), *it));
			}
			else it++;
		}
		//when its true organism die
		else if ((*it)->action()) {
			deletePosition(*it);
			delete* it;
			it = initiativeList.erase(find(initiativeList.begin(), initiativeList.end(), *it));
		}
		else it++;
		drawWorld();
		cout << information;
		setInformations(-1, nullptr, nullptr);
	}
	//all organism get ready to copulate in next turn
	it = initiativeList.begin();
	while (it != initiativeList.end()) {
		if (!(*it)->getReproduce()) {
			(*it)->setReproduce(1);
		}
		it++;
	}
}

void World::setPosition(Organism *organism) {
	this->map[organism->getPosX()][organism->getPosY()] = organism;
}
void World::deletePosition(Organism* organism) {
	this->map[organism->getPosX()][organism->getPosY()] = nullptr;
}

void World::addOrganism(Organism *organism) {
	this->map[organism->getPosX()][organism->getPosY()] = organism;

	initiativeList.push_back(organism);
	//  relegate organism to his initaitive position
	for (list<Organism*>::iterator it = initiativeList.begin(); it != initiativeList.end(); it++) {
		if ((*it)->getInitiative() < organism->getInitiative()) {
			initiativeList.insert(it, organism);
			initiativeList.pop_back();
			break;
		}
	}
}
void World::deleteOrganism(Organism* organism) {
	// if oragnism still exist on map deleting his position
	if(this->getOrganism(organism->getPosX(), organism->getPosY()) == organism) 
		this->deletePosition(organism);
	
	initiativeList.erase(find(initiativeList.begin(), initiativeList.end(), organism));

	delete organism;
}

//drawing
void World::drawWorld() {
	system("cls");
	cout << "Tomasz Czochanski 176062" << endl;
	for (int i = 0; i < getSizeY() + 2; i++) cout << "#";
	cout << endl;
	for (int i = 0; i < getSizeX(); i++) {
		cout << "#";
		for (int j = 0; j < getSizeY(); j++) {
			if (map[i][j] == nullptr) {
				cout << " ";
			}
			else {
				map[i][j]->drawSymbol();
			}
		}
		cout << "#";
		drawInstruction(i);
		cout << endl;
	}
	for (int i = 0; i < getSizeY() + 2; i++) cout << "#";
	cout << endl;
	cout << "Informations:" << endl;
}
void World::drawInstruction(int i) {
	switch (i) {
	case 0: cout << "	" << "spacebar - next organism";
		break;
	case 1: cout << "	" << "w,a,s,d - move";
		break;
	case 2: cout << "	" << "r - special ability";
		break;
	case 3: cout << "	" << "ESC - quit";
		break;
	case 4: cout << "	" << "Turn number: " << getTurn();
		break;
	}
}
void World::setInformations(int i, Organism* org, Organism* enemy) {
	switch (i) {
		//0 is for organism killed an enemy
	case 0:
		this->information += (char)org->getSymbol();
		this->information+= "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") has killed "
			+ enemy->getSymbol() + " (" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ")" + "\n";
		break;
		//1 is for being born
	case 1:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") was born" + "\n";
		break;
		//2 is for become adult
	case 2:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") has grown" + "\n";
		break;
		//telling that organism already made his turn
	case 4:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") already made his action" + "\n";
		break;
		//telling that oragnism has esacped
	case 5:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") trying to kill "
			+ enemy->getSymbol() + " (" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ")" + "\n";
		this->information += (char)enemy->getSymbol();
		this->information += "(" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ") has escaped " + "\n";
		break;
		//telling that organism deflected attack
	case 6:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") trying to kill "
			+ enemy->getSymbol() + " (" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ")" + "\n";
		this->information += (char)enemy->getSymbol();
		this->information += "(" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ") has deflected attack " + "\n";
		break;
		//telling about boost
	case 7:
		this->information += (char)enemy->getSymbol();
		this->information += "(" + to_string(enemy->getPosX()) + ", " + to_string(enemy->getPosY()) + ") give boost to "
			+ org->getSymbol() + " (" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ")" + "\n";
		break;
		//telling about keys to choose
	case 8:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") choose w,s,a,d to move or r to special" + "\n";
		break;
	case 9:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") acctivated antelope speed" + "\n";
		break;
		//telling whose turn now
	case 10: this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ")" + "\n";
		break;
	default:
		this->information = "";
		break;
	}
}

//gets
Organism* World::getOrganism(int x, int y) {
	return this->map[x][y];
}
unsigned char World::getZn() {
	return this->zn;
}
int World::getSizeX() {
	return this->sizeX;
}
int World::getSizeY() {
	return this->sizeY;
}
unsigned int World::getTurn() {
	return this->turn;
}

//Free memory of every Organism
World::~World() {
	if (map != nullptr) {
		for (int i = 0; i < getSizeX(); i++) {
			for (int j = 0; j < getSizeY(); j++) delete map[i][j];
			delete[] map[i];
		}
		delete[] map;
	}
}