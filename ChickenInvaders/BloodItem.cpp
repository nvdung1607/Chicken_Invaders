#include "BloodItem.h"
#include <iostream>
/*
	Set update
*/

void BloodItem::update() {
	this->sprite.move(0.f, 10.f);
}

/*
	Render vat pham mau
*/
void BloodItem::render(sf::RenderTarget& target) {
	//sf::RenderStates states;
	//states.blendMode = sf::BlendNone;
	target.draw(this->sprite);
}

sf::FloatRect BloodItem::getBounds() {
	return this->sprite.getGlobalBounds();
}

int BloodItem::getHealthAmount() {
	return healthAmount;
}

BloodItem::BloodItem(sf::Texture* texture, sf::Vector2f position)
{
	sprite.setTexture(*texture);
	sprite.setPosition(position);
	sprite.setScale(0.09f, 0.09f);
	sf::Texture::bind(NULL);
}
/*
void BloodItem::draw(sf::RenderWindow& window){
	window.draw(sprite);
}*/
BloodItem::~BloodItem(void)
{
}
