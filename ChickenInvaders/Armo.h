#pragma once

#include <SFML/Graphics.hpp>

class Armo
{
	sf::Sprite a_Sprite;
	sf::Texture a_Texture;
	sf::Vector2f direction;

	float speed;
	float attackCooldown;
	float attackCooldownMax;

	//Init Function
	void initTexture();
	void initSprite();
public:
	Armo();
	Armo(sf::Texture* a_Texture, float pos_x, float pos_y, float dir_X, float dir_Y);
	virtual ~Armo(void);

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget& target);
};

