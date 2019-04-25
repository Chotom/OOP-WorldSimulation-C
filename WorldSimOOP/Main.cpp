#include <iostream>
#include <conio.h>
#include "World.h"
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	int x, y;
	string name;
	char zn = 0;
	
	cout << "n - new Game" << endl;
	cout << "l - load game" << endl;
	cout << "others - quit" << endl;
	zn = _getch();

	if (zn == 'n') {
		cout << "Give size of map" << endl;
		cin >> x >> y;
		World world(x, y);
		world.startGame();
	}
	else if (zn == 'l') {
		cout << "Give name of file to load" << endl;
		cin >> name;
		try {
			World world(name);
			world.startGame();
		}
		catch (const std::invalid_argument & e) {}
	}

	return 0;
}