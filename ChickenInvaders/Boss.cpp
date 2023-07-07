#include "Boss.h"
#include <iostream>

Boss::Boss(void)
{
	this->movementSpeed = 3.f;
	this->HPMax = 200;
	this->HP = this->HPMax;
	this->texture.loadFromFile("img/messi.png");
	this->sprite.setTexture(texture);
	this->sprite.setPosition(800.f, 450.f);
	this->sprite.setScale(0.35f, 0.35f);

	dir = 0;
	moveX = -this->movementSpeed;
	moveY = -this->movementSpeed;
}

const sf::FloatRect Boss::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Boss::getPosition() const
{
	return this->sprite.getPosition();
}

Boss::~Boss(void)
{
}


int Boss::getHP()
{
	return this->HP;
}

int Boss::getHPMax()
{
	return this->HPMax;
}

void Boss::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Boss::appear()
{
	if (sprite.getPosition().y < 300)
	{
		//this->sprite.move(0.f, 4.f);
	}
}
void Boss::moveBoss()
{
	if (this->HP <= 150 && this->HP > 100) this->movementSpeed = 4.f;
	if (this->HP <= 100 && this->HP > 75) this->movementSpeed = 5.f;
	if (this->HP <= 75 && this->HP > 40) this->movementSpeed = 8.f;
	if (this->HP <= 40 && this->HP > 20) {
		this->movementSpeed = 15.f;
	}
	if (this->HP <= 20 && this->HP >= 0) this->movementSpeed = 20.f;
	//logic xet huong di chuyen
	if (dir == 0) {
		moveX = -this->movementSpeed;
		moveY = -this->movementSpeed;
	}
	else if (dir == 1) {
		moveX = +this->movementSpeed;
		moveY = -this->movementSpeed;
	}
	else if (dir == 2) {
		moveX = +this->movementSpeed;
		moveY = +this->movementSpeed;
	}
	else if (dir == 3) {
		moveX = -this->movementSpeed;
		moveY = +this->movementSpeed;
	}

	//logic check va cham goc
	if (dir == 0) {
		if (this->getPosition().y <= 0) dir = 3;
		else
			if (this->getPosition().x <= 0) dir = 1;
	}
	else if (dir == 1) {
		if (this->getPosition().y <= 0) dir = 2;
		else
			if (this->getPosition().x >= 1400) dir = 0;
	}
	else if (dir == 2) {
		if (this->getPosition().x >= 1400) dir = 3;
		else
			if (this->getPosition().y >= 750) dir = 1;
	} if (dir == 3) {
		if (this->getPosition().y >= 750) dir = 0;
		else
			if (this->getPosition().x <= 0) dir = 2;
	}

	//di duyen bosss
	this->sprite.move(moveX, moveY);
}

void Boss::loseHP(int value)
{
	this->HP -= 1;
}