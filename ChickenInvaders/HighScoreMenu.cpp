#include <iostream>
#include <string>
#include <functional>
#include "HighscoreMenu.h"
#define _CRT_SECURE_NO_DEPRECATE
#define SFML_NO_DEPRECATED_WARNINGS

void HighscoreMenu::loadFromText() {
	std::freopen("highscores.txt", "r", stdin);
	for (int i = 0; i < MAX_HIGHSCORE_CAPACITY; i++) {
		int temp;
		std::cin >> temp;
		highscores.push_back(temp);
	}
}


void HighscoreMenu::draw(sf::RenderWindow& window) {
	window.draw(s_background);
	for (int i = 0; i < MAX_HIGHSCORE_CAPACITY; i++) {
		hcText[i].setScale(sf::Vector2f(1.5f, 1.5f));
		window.draw(hcText[i]);

	}
	defaultText.setCharacterSize(24);
	window.draw(defaultText);
}

bool HighscoreMenu::isHighscore(int val) {
	if (val >= highscores[MAX_HIGHSCORE_CAPACITY - 1]) {
		return true;
	}
	return false;
}

void HighscoreMenu::updateHighscores(int val) {
	highscores.pop_back();
	highscores.push_back(val);
	std::cout << "Da vao day ne";
	for (int i = 0; i < MAX_HIGHSCORE_CAPACITY - 1; i++) {
		for (int j = i + 1; j < MAX_HIGHSCORE_CAPACITY; j++) {
			if (highscores[j] >= highscores[i]) {
				int temp = highscores[i];
				highscores[i] = highscores[j];
				highscores[j] = temp;
			}
		}
	}
	std::freopen("highscores.txt", "w", stdout);
	for (int i = 0; i < MAX_HIGHSCORE_CAPACITY; i++) {
		std::cout << std::to_string(highscores[i]) << " ";
	}
}

void HighscoreMenu::initHighscores(float width, float height) {
	hcText[0].setFont(font);
	hcText[0].setColor(sf::Color::White);
	std::string hc0 = std::to_string(highscores[0]);
	hcText[0].setString("1         " + hc0);
	//hcText[0].setScale(2.0f);
	hcText[0].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 5));

	hcText[1].setFont(font);
	hcText[1].setColor(sf::Color::White);
	std::string hc1 = std::to_string(highscores[1]);
	hcText[1].setString("2         " + hc1);
	//hcText[0].setScale(2.0f);
	hcText[1].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 6));

	hcText[2].setFont(font);
	hcText[2].setColor(sf::Color::White);
	std::string hc2 = std::to_string(highscores[2]);
	hcText[2].setString("3         " + hc2);
	//hcText[0].setScale(2.0f);
	hcText[2].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 7));

	hcText[3].setFont(font);
	hcText[3].setColor(sf::Color::White);
	std::string hc3 = std::to_string(highscores[3]);
	hcText[3].setString("4         " + hc3);
	//hcText[0].setScale(2.0f);
	hcText[3].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 8));

	hcText[4].setFont(font);
	hcText[4].setColor(sf::Color::White);
	std::string hc4 = std::to_string(highscores[4]);
	hcText[4].setString("5         " + hc4);
	//hcText[0].setScale(2.0f);
	hcText[4].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 9));

	defaultText.setFont(font);
	defaultText.setColor(sf::Color::Red);
	defaultText.setString("Press Enter to get back Menu");
	defaultText.setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_HIGHSCORE_CAPACITY + 9) * 10));
}

HighscoreMenu::HighscoreMenu(float width, float height)
{
	this->loadFromText();
	if (!font.loadFromFile("fonts/prstartk.ttf")) {
		std::cout << "Loi load font";
	}
	hcText[0].setFont(font);
	hcText[0].setColor(sf::Color::White);
	std::string hc0 = std::to_string(highscores[0]);
	hcText[0].setString("1         " + hc0);
	//hcText[0].setScale(2.0f);
	hcText[0].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 5));

	hcText[1].setFont(font);
	hcText[1].setColor(sf::Color::White);
	std::string hc1 = std::to_string(highscores[1]);
	hcText[1].setString("2         " + hc1);
	//hcText[0].setScale(2.0f);
	hcText[1].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 6));

	hcText[2].setFont(font);
	hcText[2].setColor(sf::Color::White);
	std::string hc2 = std::to_string(highscores[2]);
	hcText[2].setString("3         " + hc2);
	//hcText[0].setScale(2.0f);
	hcText[2].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 7));

	hcText[3].setFont(font);
	hcText[3].setColor(sf::Color::White);
	std::string hc3 = std::to_string(highscores[3]);
	hcText[3].setString("4         " + hc3);
	//hcText[0].setScale(2.0f);
	hcText[3].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 8));

	hcText[4].setFont(font);
	hcText[4].setColor(sf::Color::White);
	std::string hc4 = std::to_string(highscores[4]);
	hcText[4].setString("5         " + hc4);
	//hcText[0].setScale(2.0f);
	hcText[4].setPosition(sf::Vector2f(width / 2 - 300, height / (MAX_HIGHSCORE_CAPACITY + 9) * 9));

	defaultText.setFont(font);
	defaultText.setColor(sf::Color::Red);
	defaultText.setString("Press Enter to get back Menu");
	defaultText.setPosition(sf::Vector2f(width / 2 - 250, height / (MAX_HIGHSCORE_CAPACITY + 9) * 10));

	e_background.loadFromFile("img/menu.png");
	s_background.setTexture(e_background);
}


HighscoreMenu::~HighscoreMenu(void)
{
}
