#pragma once
#include<SFML/Graphics.hpp>
#include "Egg.h"
class Chicken
{
private:
	sf::Sprite srpite;
	int movementSpeed;
	//Functions
	void initVariables();
	int randX;
	int randY;
public:
	Chicken(sf::Texture* texture, float posX, float posY);
	virtual ~Chicken();
	//Accessor
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	//Function
	void render(sf::RenderTarget* target);
	void update();
	void moveHorizontal();
	void moveVertical();
	void moveInPatter();
	void moveMeteorite();
	void decreaseHP();
	void dropEgg(float posX, float posY);
	int getHP();
	void loseHp(const int value);
	int p;
	int HP;
};