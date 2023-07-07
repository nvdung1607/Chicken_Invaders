#pragma once
#pragma warning(4:4596)
#include<SFML/Graphics.hpp>
class Egg
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	//Attribute
	//Functions
	void initVariables();
public:
	Egg(float posX, float posY);
	Egg(sf::Texture* texture, float posX, float posY);
	float movementSpeed;
	virtual ~Egg();
	//Function
	void moveVertical();
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
	//Hom nay
	void Egg::bossShoot1();
	void Egg::bossShoot2();
	void Egg::bossShoot3();
};