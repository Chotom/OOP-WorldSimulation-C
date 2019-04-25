#include <iostream>
#include <conio.h>
#include "World.h"
#include <time.h>


int main() {
	srand(time(NULL));
	int x, y;
	std::cin >> x >> y;
	//dodac try catch
	World world(x, y);
	world.startGame();

	return 0;
}