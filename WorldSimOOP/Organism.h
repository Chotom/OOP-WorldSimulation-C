#pragma once
#include "World.h"
#include <tuple>

class Organism{
private:
	bool randomiseEscape(Organism*, int, int);
	bool getDefence();
	bool getBoost();
protected:
	int posX, posY, strength, initiative, boost;
	bool canEscape, canDef, canPoison, canReproduce;
	char symbol;
	World *world;
public:
	Organism();
	Organism(int, int, World&);
	Organism(int, int, World&, int);
	virtual ~Organism();
	
	virtual bool action() = 0;
	virtual Organism* reproduce(int, int) = 0;
	virtual bool collision(Organism*, int, int);
	void drawSymbol();

	void setStrength(int);
	void setReproduce(bool);
	void setSymbol();

	int getStrength();
	bool getPoison();
	int getInitiative();
	int getPosX();
	int getPosY();
	char getSymbol();
	bool getReproduce();
};