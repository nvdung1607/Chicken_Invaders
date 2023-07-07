#include "Egg.h"
#include <iostream>
void Egg::initVariables()
{
	this->movementSpeed = 10.f;
}
Egg::Egg(float posX, float posY)
{
	this->initVariables();
	this->texture.loadFromFile("img/giayvang.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(0.18f, 0.18f);
	this->sprite.setPosition(posX, posY);
}
Egg::Egg(sf::Texture* texture, float posX, float posY)
{
	this->initVariables();
	this->sprite.setTexture(*texture);
	this->sprite.setScale(0.55f, 0.55f);
	this->sprite.setPosition(posX, posY);
}
Egg::~Egg()
{
}
void Egg::update()
{
}


void Egg::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
void Egg::moveVertical()
{
	this->sprite.move(0.f, this->movementSpeed);
}

const sf::FloatRect Egg::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
void Egg::bossShoot1()
{
	std::vector<sf::Vector2f> shootDirection;
	shootDirection.push_back(sf::Vector2f(-1.0f, 1.0f));
	for (auto& direction : shootDirection)
	{
		this->sprite.move((this->movementSpeed - 5) * direction.x, (this->movementSpeed - 5) * direction.y);
	}
}

void Egg::bossShoot2()
{
	std::vector<sf::Vector2f> shootDirection;
	shootDirection.push_back(sf::Vector2f(0.0f, 1.0f));
	for (auto& direction : shootDirection)
	{
		this->sprite.move((this->movementSpeed - 5) * direction.x, (this->movementSpeed - 5) * direction.y);
	}
}
void Egg::bossShoot3()
{
	std::vector<sf::Vector2f> shootDirection;
	shootDirection.push_back(sf::Vector2f(1.0f, 1.0f));
	for (auto& direction : shootDirection)
	{
		this->sprite.move((this->movementSpeed - 5) * direction.x, (this->movementSpeed - 5) * direction.y);
	}
}