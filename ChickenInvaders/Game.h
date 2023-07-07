#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <ctime>
#include "Ship.h"
#include "Armo.h"
#include "BloodItem.h"
#include <SFML/Audio.hpp>
#include "Chicken.h"
#include "Egg.h"
#include <cstdlib>
#include "Menu.h"
#include "HighscoreMenu.h"
#include "Boss.h"
class Game
{
private:
	//Define game environment
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//Map textures
	std::map<std::string, sf::Texture*> textures;

	//world
	sf::Sprite worldBackGround;
	sf::Texture worldBackGroundTex;

	//Game Logic
	float healthItemSpawnTimer;
	float healthItemSpawnTimerMax;
	int maxHealthItems;
	int points;
	int level;
	//Sound Effect
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::SoundBuffer bufferBackground;
	sf::Sound soundBackground;
	//Sound Collision
	sf::SoundBuffer chickenKilledBuffer;
	sf::Sound soundChickenKilled;
	sf::SoundBuffer bonkBuffer;
	sf::Sound soundBonk;
	sf::SoundBuffer ankaraBuffer;
	sf::Sound soundAnkara;
	sf::SoundBuffer ingameBuffer;
	sf::Sound soundIngame;
	sf::SoundBuffer harryBuffer;
	sf::Sound soundHarry;
	sf::SoundBuffer explosionBuffer;
	sf::Sound soundExplosion;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound soundGameOver;
	//Fonts and Texts
	sf::Font font;
	sf::Text scoreText;
	sf::Text hpText;
	sf::Text gameOverText;
	sf::Text levelText;
	sf::Text winText;

	//Game object
	Ship* ship;
	HighscoreMenu* hcMenu;

	std::vector<Armo*> armos;
	sf::RectangleShape healthItem;
	std::vector<BloodItem*> bloodItems;
	std::vector<sf::RectangleShape> healthItems;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	sf::RectangleShape bossHpBar;
	sf::RectangleShape bossHpBarBack;

	//Chicken
	std::vector<Chicken*> chickens;
	int randX;
	int randY;
	sf::Clock clock;
	sf::Clock clockBossShip;

	//Egg
	std::vector<Egg*> eggs;
	//Time render eggs
	float dropEggThreshold; // Ngưỡng thời gian giữa các lần thả trứng
	float dropEggTimer;
	float dropEggTimerBoss;
	float dropEggThresholdBoss;

	Boss* boss;
	std::vector<Egg*> bossEggs1;
	std::vector<Egg*> bossEggs2;
	std::vector<Egg*> bossEggs3;

	bool isBossLevel;

	//private functions
	void initVariable();
	void initWindow();
	void initGui();
	void initShip();
	void initArmo();
	void initBloodItem();
	void initWorld();
	void initSound();
	void initChicken(int level);
	void initEggs();
	void initBoss();
public:
	Game(void);
	virtual ~Game(void);

	//Accessor
	const bool isRunning() const;
	void run();
	void pollEvents();
	void update();
	void updateArmos();
	void updateGui();
	void render();
	void renderGui(sf::RenderTarget* target);

	// Function by Quan Trinh
	void updateMousePosition();
	void initHealthItem();
	void spawnHealthItems();
	void updateHealthItems();
	void renderHealthItems();
	void updateBloodItems();
	void renderWorld();
	void updateWorld();
	void updateCollision();
	void updateChicken(int level);
	void updateEgg();
	void collisionEggChicken();
	void listenKeyBoard();
	void collisionChickenShip();
	void collisionShipHpItem();
	void updateBoss();

	//restart game

	int gameStatus;
	void restart();

};

