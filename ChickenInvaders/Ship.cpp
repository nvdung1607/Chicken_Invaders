#include "Ship.h"

void Ship::initTexture() {
	if (!this->s_Texture.loadFromFile("img/ship.png"))
	{
		// error...
	}
}

void Ship::initVariables() {
	this->speed = 5;
	this->attackCooldownMax = 6.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 10
		;
	this->hp = this->hpMax;
}
void Ship::initSprite() {
	this->s_Sprite.setTexture(this->s_Texture);
	this->s_Sprite.setPosition(this->x, this->y);
	this->s_Sprite.setScale(0.30, 0.30);
}

const bool Ship::canAttack() {
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
void Ship::updateAttack() {
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Ship::update() {
	this->updateAttack();
}

const sf::Vector2f& Ship::getPos() const {
	return this->s_Sprite.getPosition();
}

const int& Ship::getHp() const {
	return this->hp;
}

const int& Ship::getHpMax() const {
	return this->hpMax;
}

void Ship::move(float x, float y) {
	this->s_Sprite.setPosition(x, y);
}

void Ship::rotate(float deg) {
	this->s_Sprite.setRotation(deg);
	this->s_Sprite.rotate(10.f);
}

const sf::FloatRect Ship::getBounds() const {
	return this->s_Sprite.getGlobalBounds();
}

void Ship::setPosition(const sf::Vector2f pos) {
	this->s_Sprite.setPosition(pos);
}

void Ship::setPosition(const float x, const float y) {
	this->s_Sprite.setPosition(x, y);
}

void Ship::setHp(const int hp) {
	this->hp = hp;
}

void Ship::loseHp(const int value) {
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
	if (this->hp > 10) {
		this->hp = 10;
	}
}


Ship::Ship(void)
{
	this->x = 700;
	this->y = 550;
	this->armo_capacity = 1;
	this->initVariables();
	this->initTexture();
	this->initSprite();
}


Ship::~Ship(void)
{

}

void Ship::render(sf::RenderTarget& target) {
	target.draw(this->s_Sprite);
}
