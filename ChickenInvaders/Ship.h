#pragma once

#include <SFML/Graphics.hpp>

class Ship
{
private:
	// Hello world
	sf::Event event;
	sf::Sprite s_Sprite;
	sf::Texture s_Texture;

	float x;
	float y;
	int speed;
	int hp;
	int hpMax;
	int armo_capacity;

	float attackCooldown;
	float attackCooldownMax;

	//Init Function
	void initTexture();
	void initSprite();
	void initVariables();
public:
	Ship(void);
	~Ship(void);

	//Accessor
	const sf::Vector2f& getPos() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Functions
	void move(float x, float y);
	void rotate(float deg);
	void update();
	void updateAttack();
	const sf::FloatRect getBounds() const;
	void render(sf::RenderTarget& target);
	const bool canAttack();

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
};

