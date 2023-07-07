#include "Armo.h"

Armo::Armo(sf::Texture* a_Texture, float pos_x, float pos_y, float dir_X, float dir_Y)
{
	this->a_Sprite.setTexture(*a_Texture);
	this->a_Sprite.setPosition(pos_x, pos_y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->a_Sprite.setScale(0.2f, 0.2f);
	this->speed = 15.f;
}

const sf::FloatRect Armo::getBounds() const {
	return this->a_Sprite.getGlobalBounds();
}

Armo::~Armo(void)
{
}

void Armo::update() {
	this->a_Sprite.move(this->speed * this->direction);
}

const sf::Vector2f& Armo::getPos() const {
	return this->a_Sprite.getPosition();
}

void Armo::render(sf::RenderTarget& target) {
	target.draw(this->a_Sprite);
}
