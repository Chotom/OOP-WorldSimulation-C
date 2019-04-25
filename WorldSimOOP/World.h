#pragma once
#include <list>
#include <String>

class Organism;

class World {
private:
	int sizeX, sizeY;
	unsigned int turn;
	unsigned char zn;
	Organism ***map;
	std::list<Organism*> initiativeList;
	std::string information; 
	void drawWorld();
	void drawInstruction(int);
	unsigned int getTurn();
	void safeGame();
public:
	World(std::string);
	World(int, int);
	~World();
	void startGame();
	void addOrganism(Organism*);
	
	void setPosition(Organism*);
	void setInformations(int, Organism*, Organism*);
	void setNextTurn();

	void deleteOrganism(Organism*);
	void deletePosition(Organism*);

	Organism* getOrganism(int, int);
	unsigned char getZn();
	int getSizeX();
	int getSizeY();

	
};