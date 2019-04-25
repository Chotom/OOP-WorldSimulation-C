#include <iostream>
#include <fstream>
#include <conio.h>
#include <String>
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
	
World::World(string name) {
	fstream fileSave;
	fileSave.open("D:\\Documents\\Repo\\Cpp\\WorldSimOOP\\saves\\" + name + ".sv", std::ios::in);
	if (fileSave.good() == true) {

		fileSave >> this->sizeX >> this->sizeY >> this->turn;
		if(sizeX < 1 || sizeY < 1) throw invalid_argument("invalid data in file");
		else {
			//fill map with empty organisms
			this->map = new Organism **[sizeX];
			for (int i = 0; i < sizeX; i++) map[i] = new Organism * [sizeY]();

			while (!fileSave.eof()) {
				char symbol;
				int x, y, strength, cooldown;
				fileSave >> symbol >> x >> y >> strength;
				switch (symbol) {
				case 'A':
					addOrganism(new Antelope(x, y, *this, strength));
					break;
				case 'H':
					fileSave >> cooldown;
					addOrganism(new Human(x, y, *this, strength, cooldown));
					break;
				case 'O':
					addOrganism(new Sheep(x, y, *this, strength));
					break;
				case 'W':
					addOrganism(new Wolf(x, y, *this, strength));
					break;
				case '|':
					addOrganism(new Grass(x, y, *this));
					break;
				case '*':
					addOrganism(new Dandelion(x, y, *this));
					break;
				case 'F':
					addOrganism(new Fox(x, y, *this, strength));
					break;
				case 'T':
					addOrganism(new Turtle(x, y, *this, strength));
					break;
				case 'G':
					addOrganism(new Guarana(x, y, *this));
					break;
				case 'D':
					addOrganism(new DeadlyNightshade(x, y, *this));
					break;
				case 'X':
					addOrganism(new SosnowskyHogweed(x, y, *this));
					break;
				}
			}
		}
	}
	else  throw invalid_argument("This file name doesnt exist");
	
	this->zn = 0;
	this->information = "";


	list<Organism*>::iterator it = initiativeList.begin();
	it = initiativeList.begin();
	while (it != initiativeList.end()) {
		if (!(*it)->getReproduce()) {
			if (!((*it)->getSymbol() <= 'Z' && (*it)->getSymbol() >= 'A')) {
				setInformations(2, (*it), nullptr);
				(*it)->setSymbol();
			}
			(*it)->setReproduce(1);
		}
		it++;
	}
}

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
	addOrganism(new Antelope(1, 5, *this));
	addOrganism(new Guarana(2, 2, *this));
	addOrganism(new Dandelion(4, 4, *this));
	addOrganism(new Human(1, 1, *this));
	addOrganism(new SosnowskyHogweed(4, 5, *this));
	addOrganism(new Wolf(3, 3, *this));
	addOrganism(new Fox(2, 3, *this));
}

void World::startGame() {
	while(zn != 27) {
		drawWorld();
		setNextTurn();
	}
}
void World::setNextTurn() {
	

	//do action of every organism on the list
	list<Organism*>::iterator it = initiativeList.begin();
	
	//
	setInformations(11, nullptr, nullptr);
	cout << information;
	setInformations(-1, nullptr, nullptr);
	zn = _getch();
	drawWorld();
	//
	if (zn == 'z') this->safeGame();
	this->turn++;

	while (it != initiativeList.end()) {
		
		/*zn = _getch();
		if (zn != 32) continue;*/
		if (zn == 27) break;

		/*setInformations(10, (*it), nullptr);*/

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
			/*drawWorld();*/
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
		/*cout << information;
		setInformations(-1, nullptr, nullptr);*/
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
	case 0: cout << "	" << "spacebar - next turn";
		break;
	case 1: cout << "	" << "w,a,s,d - move";
		break;
	case 2: cout << "	" << "r - special ability";
		break;
	case 3: cout << "	" << "ESC - quit";
		break;
	case 4: cout << "	" << "Turn number: " << getTurn();
		break;
	case 5: cout << "	" << "z - save game";
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
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") its human turn" + "\n";
		break;
	case 9:
		this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ") acctivated antelope speed" + "\n";
		break;
		//telling whose turn now
	case 10: this->information += (char)org->getSymbol();
		this->information += "(" + to_string(org->getPosX()) + ", " + to_string(org->getPosY()) + ")" + "\n";
		break;
	case 11: this->information += "Turn ended \n";
		break;
	case 12: this->information += "cant safe game in 0 turn \n";
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

//saving game
void World::safeGame() {
	if (this->getTurn() == 0) this->setInformations(12, nullptr, nullptr);
	else {
		cout << "Give file name to safe game:" << endl;
		string name;
		cin >> name;
		fstream map;
		map.open("D:\\Documents\\Repo\\Cpp\\WorldSimOOP\\saves\\" + name + ".sv", std::ios::out);
		if (map.good() == true)
		{
			map << this->getSizeX() << " " << this->getSizeY() << " " << this->getTurn() << endl;

			for (list<Organism*>::iterator it = initiativeList.begin(); it != initiativeList.end(); it++) {
				map << (*it)->getSymbol() << " ";
				map << (*it)->getPosX() << " " << (*it)->getPosY() << " " << (*it)->getStrength();
				if (Human * h = dynamic_cast<Human*>((*it))) map << " " << h->getCooldown();
				map << endl;
			}
			map.close();
		}
		else exit;
	}
}

//Free memory of every Organism
World::~World() {
	information.clear();
	if (map != nullptr) {
		for (int i = 0; i < getSizeX(); i++) {
			for (int j = 0; j < getSizeY(); j++) delete map[i][j];
			delete[] map[i];
		}
		delete[] map;
	}
	initiativeList.clear();
}