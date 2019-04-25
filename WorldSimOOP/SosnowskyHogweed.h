#pragma once
#include "Plant.h"


class SosnowskyHogweed : public Plant {
public:
	SosnowskyHogweed(int, int, World&);
	~SosnowskyHogweed();
	bool action();
	Organism* reproduce(int, int);
};