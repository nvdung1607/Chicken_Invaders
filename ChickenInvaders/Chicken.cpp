#include "Chicken.h"
#include <cmath>
void Chicken::initVariables()
{
	this->HP = 3;
	this->movementSpeed = 4.0f;
}
Chicken::Chicken(sf::Texture* texture, float posX, float posY)
{
	this->initVariables();
	this->srpite.setTexture(*texture);
	this->srpite.setPosition(posX, posY);
	this->srpite.setScale(0.12f, 0.12f);
}
Chicken::~Chicken()
{
}
const sf::Vector2f Chicken::getPosition() const
{
	return this->srpite.getPosition();
}
void Chicken::render(sf::RenderTarget* target)
{
	target->draw(this->srpite);
}
void Chicken::update()
{
}
void Chicken::moveHorizontal() {
	sf::Vector2f movement = sf::Vector2f(movementSpeed, 0.f);
	// Di chuyển gà
	this->srpite.move(movement);
	// Kiểm tra va chạm với cạnh trái màn hình
	if (getPosition().x < 0) {
		movementSpeed *= -1;
	}
	// Kiểm tra va chạm với cạnh phải màn hình
	else if (getPosition().x > 1500) {
		movementSpeed *= -1;
	}
}

void Chicken::moveVertical() {
	sf::Vector2f movement = sf::Vector2f(0.f, movementSpeed + 2.f);
	// Di chuyển gà
	this->srpite.move(movement);
	// Kiểm tra va chạm với cạnh trái màn hình
	if (getPosition().y > 1500) {
		//movementSpeed *= -1;
		float temp = this->srpite.getPosition().x;
		this->srpite.setPosition(temp, 0);
	}
	// Kiểm tra va chạm với cạnh phải màn hình
	//else if (getPosition().y > 500) {
		//movementSpeed *= -1;
	//}
}

void Chicken::moveMeteorite() {
	if (p == 0) {
		sf::Vector2f movement = sf::Vector2f(-5.f, 3.f);
		this->srpite.move(movement);
		//std::srand(static_cast<unsigned>(std::time(0)));
		randX = std::rand() % 700 + 900;
		randY = std::rand() % 200;

		if (getPosition().y > 900) {
			//movementSpeed *= -1;
			//std::cout << randX << " " << randY << "\n";
			this->srpite.setPosition(randX, randY);
		}
	}
	else if (p == 1) {
		sf::Vector2f movement = sf::Vector2f(5.f, 3.f);
		this->srpite.move(movement);
		//std::srand(static_cast<unsigned>(std::time(0)));
		randX = std::rand() % 700;
		randY = std::rand() % 200;

		if (getPosition().y > 900) {
			//movementSpeed *= -1;
			//std::cout << randX << " " << randY << "\n";
			this->srpite.setPosition(randX, randY);
		}
	}
}

void Chicken::loseHp(const int value) {
	this->HP -= value;
	if (this->HP < 0) {
		this->HP = 0;
	}
}

const sf::FloatRect Chicken::getBounds() const {
	return this->srpite.getGlobalBounds();
}
