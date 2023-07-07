#pragma once
#include "Egg.h"
class Boss {
private:
	int HP;
	int HPMax;
	float movementSpeed;

	sf::Texture texture;
	sf::Sprite sprite;

public:

	//Accessor
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	int getHP();
	int getHPMax();
	Boss(void);
	~Boss(void);
	//Ban trung
	void shootEggs(float posX, float posY);
	void update();
	void render(sf::RenderTarget& target);
	void moveBoss();
	void appear();
	void loseHP(int value);

	//huong di chuyen
	int dir;

	float moveX;
	float moveY;
};

