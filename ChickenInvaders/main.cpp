#include<iostream>
#include<SFML/Graphics.hpp>
#include<ctime>
#include "Game.h"

using namespace std;

int main()
{
	system("cls");
	srand(static_cast<unsigned>(time(NULL)));
	Game game;

	game.run();

	return 0;
}