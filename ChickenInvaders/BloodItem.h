#pragma once

#include <SFML/Graphics.hpp>

class BloodItem
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	//Init blood Item.
	void initTexture();
	void initSprite();
	int healthAmount;
public:
	BloodItem(sf::Texture* texture, sf::Vector2f position);
	virtual ~BloodItem(void);

	//Functions
	void update();
	void render(sf::RenderTarget& target);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds();
	int getHealthAmount();
};

