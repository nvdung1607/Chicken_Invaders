#include <iostream>

#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("fonts/prstartk.ttf")) {
		std::cout << "Loi load font";
	}
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	//menu[0].setScale(2.0f);
	menu[0].setPosition(sf::Vector2f(width / 2 - 90, height / (MAX_NUMBER_OF_ITEMS + 9) * 6));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("High Score");
	menu[1].setPosition(sf::Vector2f(width / 2 - 220, height / (MAX_NUMBER_OF_ITEMS + 9) * 7));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2 - 90, height / (MAX_NUMBER_OF_ITEMS + 9) * 8));

	selectedItemIndex = 0;

	e_background.loadFromFile("img/menu.png");
	s_background.setTexture(e_background);
}

Menu::~Menu(void)
{
}

void ::Menu::draw(sf::RenderWindow& windown) {
	windown.draw(s_background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].setScale(sf::Vector2f(1.5f, 1.5f));
		windown.draw(menu[i]);

	}

}

void Menu::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
