#pragma once
#pragma warning(4:4996)
#include <SFML\Graphics.hpp>

const int MAX_NUMBER_OF_ITEMS = 3;

class Menu
{
public:
	Menu(float width, float height);
	~Menu(void);

	void draw(sf::RenderWindow& windown);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	sf::Texture e_background;
	sf::Sprite s_background;

};