#pragma once
#pragma warning(4:4996)
#include <SFML\Graphics.hpp>

const int MAX_HIGHSCORE_CAPACITY = 5;

class HighscoreMenu
{
private:
	std::vector<int> highscores;

	int selectedItemIndex;
	sf::Font font;
	sf::Text hcText[MAX_HIGHSCORE_CAPACITY];
	sf::Text defaultText;

	sf::Texture e_background;
	sf::Sprite s_background;
public:
	HighscoreMenu(float width, float height);
	~HighscoreMenu(void);

	void loadFromText();
	void draw(sf::RenderWindow& window);
	bool isHighscore(int val);
	void updateHighscores(int val);
	int getPressedItem() { return selectedItemIndex; }
	std::vector<int> getHighscores() { return highscores; }
	void initHighscores(float width, float heights);

};

