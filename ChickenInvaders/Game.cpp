#include "Game.h"
#include "Ship.h"
#include "BloodItem.h"
#include "Armo.h"
#include<iostream>
#include <sstream>
bool writeAble;
//Init Variables for game
void Game::initVariable() {
	this->window = nullptr;
	//Quan Trinh
	this->points = 0;
	this->healthItemSpawnTimerMax = 100.f;
	this->healthItemSpawnTimer = this->healthItemSpawnTimerMax;
	this->dropEggThreshold = 20.f;
	this->dropEggTimer = this->dropEggThreshold;
	this->dropEggThresholdBoss = 40.f;
	this->dropEggTimerBoss = this->dropEggThresholdBoss;
	this->maxHealthItems = 5;
	this->level = 1;
	this->textures["CHICKEN"] = new sf::Texture();
	this->textures["CHICKEN"]->loadFromFile("img/mp3.png");
	this->textures["EGG"] = new sf::Texture();
	this->textures["EGG"]->loadFromFile("img/armo.png");
	this->textures["METEORITE"] = new sf::Texture();
	this->textures["METEORITE"]->loadFromFile("img/harry.png");
	//Sound Collision
	this->chickenKilledBuffer.loadFromFile("audio/chicken_killed.wav");
	this->soundChickenKilled.setBuffer(chickenKilledBuffer);
	this->bonkBuffer.loadFromFile("audio/bonk.wav");
	this->soundChickenKilled.setVolume(30);
	this->soundBonk.setBuffer(bonkBuffer);
	this->ankaraBuffer.loadFromFile("audio/ankara_messi.wav");
	this->soundAnkara.setBuffer(ankaraBuffer);
	this->ingameBuffer.loadFromFile("audio/in_game.wav");
	this->soundAnkara.setBuffer(ankaraBuffer);
	this->harryBuffer.loadFromFile("audio/harry.wav");
	this->soundHarry.setBuffer(harryBuffer);
	this->explosionBuffer.loadFromFile("audio/tiengno.wav");
	this->soundExplosion.setBuffer(explosionBuffer);
	this->gameOverBuffer.loadFromFile("audio/game_over.wav");
	this->soundGameOver.setBuffer(gameOverBuffer);
	this->soundIngame.setVolume(10);
	this->isBossLevel = false;
	gameStatus = 0;
}
const bool Game::isRunning() const {
	return this->window->isOpen();
}
void Game::run()
{
start:
	//delete mouse pointer
	this->window->setMouseCursorVisible(true);
	Menu menu(this->window->getSize().x, this->window->getSize().y);
	this->hcMenu = new HighscoreMenu(this->window->getSize().x, this->window->getSize().y);
menu:
	gameStatus = 0;
	//std::cout << gameStatus << "\n";
	bool isPlayMusic = true;
	this->soundBackground.play();
	this->soundBackground.setLoop(isPlayMusic);
	while (this->window->isOpen())
	{
		//std::cout << gameStatus << "\n";
		//menu
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.getPressedItem())
					{
					case 0:
						isPlayMusic = false;
						//this->window->clear();
						goto gameStart;
						//break;
					case 1:
						this->window->clear();
						goto hc_menu;
						break;
					case 2:
						this->window->close();
						break;
					}
				}
				break;
				//dong ung dung
			case sf::Event::Closed:
				this->window->close();
				break;
			}
		}
		this->window->clear();
		//ve menu
		menu.draw(*this->window);
		this->window->display();
	}
hc_menu:
	while (this->window->isOpen())
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					goto menu;
					break;
				}
				break;
				//dong ung dung
			case sf::Event::Closed:
				this->window->close();
				break;
			}
		}
		this->window->clear();
		hcMenu->draw(*this->window);
		this->window->display();
	}
gameStart:
	bool isPlaying = true;
	writeAble = true;
	soundIngame.play();
	soundBackground.stop();
	this->soundIngame.setLoop(isPlaying);
	while (this->window->isOpen())
	{
		this->pollEvents();
		if (this->ship->getHp() > 0)
		{
			this->listenKeyBoard();
			this->updateMousePosition();
			this->update();
		}
		else
		{
			soundIngame.stop();
		}
		this->render();
		//vong lap het game
		if (gameStatus == 1 || gameStatus == 2) {
			sf::Event event;
			while (this->window->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Return:
						this->window->clear();
						restart();
						goto menu;
						break;
					}
					break;
					//dong ung dung
				case sf::Event::Closed:
					this->window->close();
					break;
				}
			}
		}
	}
}
void Game::pollEvents() {
	//Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}
void Game::listenKeyBoard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->ship->move(-1, 0);
		//this->ship->rotate(-45.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->ship->move(1, 0);
		//this->ship->rotate(45.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->ship->move(0, -1);
		//this->ship->rotate(-45.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->ship->move(0, 1);
		//this->ship->rotate(-45.f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->ship->canAttack()) {
		this->armos.push_back(new Armo(this->textures["ARMO"], this->ship->getPos().x, this->ship->getPos().y, 0.f, -1.f));
		this->sound.play();
	}
}
void Game::initWindow() {
	this->videoMode.height = 900;
	this->videoMode.width = 1600;
	this->window = new sf::RenderWindow(this->videoMode, "M10 Invader", sf::Style::Titlebar | sf::Style::Close);
	//Game Limit FPS
	this->window->setFramerateLimit(60);
}
//------------Init cac doi tuong-------------------//
void Game::initGui() {
	if (!this->font.loadFromFile("fonts/prstartk.ttf")) {
		std::cout << "ERROR LOADING FONT" << std::endl;
	}
	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setCharacterSize(25);
	this->scoreText.setString("text");
	this->scoreText.setPosition(10, 10);
	//Game Over Text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	//Win text
	this->winText.setFont(this->font);
	this->winText.setFillColor(sf::Color::Red);
	this->winText.setCharacterSize(70);
	this->winText.setString("You Win");
	this->winText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	//Level Text
	this->levelText.setFont(this->font);
	this->levelText.setFillColor(sf::Color::White);
	this->levelText.setCharacterSize(25);
	this->levelText.setString("Level: ");
	this->levelText.setPosition(this->window->getSize().x - 300, 10);
	this->playerHpBar.setSize(sf::Vector2f(100.f, 10.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color::Red);
	this->bossHpBar.setSize(sf::Vector2f(150.f, 15.f));
	this->bossHpBar.setFillColor(sf::Color::Green);
	this->bossHpBarBack = this->bossHpBar;
	this->bossHpBarBack.setFillColor(sf::Color::Red);
}
void Game::initShip() {
	this->ship = new Ship();
}

void Game::initSound() {
	this->buffer.loadFromFile("audio/sut.wav");
	this->sound.setBuffer(buffer);
	this->bufferBackground.loadFromFile("audio/background1.wav");
	this->soundBackground.setBuffer(bufferBackground);
}
void Game::initWorld() {
	this->worldBackGroundTex.loadFromFile("img/background.png");
	this->worldBackGround.setTexture(this->worldBackGroundTex);
}
//Khoi tao qua bong vang
void Game::initBloodItem() {
	this->textures["BLOOD_ITEM"] = new sf::Texture();
	this->textures["BLOOD_ITEM"]->loadFromFile("img/item_1.png");
	this->bloodItems.push_back(new BloodItem(this->textures["BLOOD_ITEM"], sf::Vector2f(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)), 0.0f)));
}
void Game::initHealthItem() {
	//this->healthItem.setPosition();
	this->healthItem.setSize(sf::Vector2f(100.f, 100.f));
	this->healthItem.setScale(sf::Vector2f(0.5f, 0.5f));
	this->healthItem.setFillColor(sf::Color::Cyan);
	this->healthItem.setOutlineColor(sf::Color::Green);
	this->healthItem.setOutlineThickness(1.f);
}
//Khoi tao CR7 Siuu
void Game::initArmo() {
	this->textures["ARMO"] = new sf::Texture();
	this->textures["ARMO"]->loadFromFile("img/armo.png");
	this->textures["CUP"] = new sf::Texture();
	this->textures["CUP"]->loadFromFile("img/cup.png");
}
void Game::initBoss()
{
	this->boss = new Boss();
}
//------------Update--------------------//
void Game::updateBloodItems() {
	int count = 0;
	if (count < this->maxHealthItems) {
		if (this->healthItemSpawnTimer >= this->healthItemSpawnTimerMax) {
			this->initBloodItem();
			this->healthItemSpawnTimer = 0.f;
			count++;
		}
		else {
			this->healthItemSpawnTimer += 0.1f;
		}
	}
	//Move the healthItems
	for (auto& h : this->bloodItems) {
		h->update();
	}
}
void Game::updateArmos() {
	unsigned counter = 0;
	for (auto* armo : this->armos) {
		armo->update();
		//Armo culling
		if (armo->getBounds().top + armo->getBounds().height < 0.f)
		{
			//Delete armo
			delete this->armos.at(counter);
			this->armos.erase(this->armos.begin() + counter);
			--counter;
		}
		++counter;
	}
}
void Game::updateWorld() {
}
void Game::updateGui() {
	std::stringstream ssScore;
	std::stringstream ssText;
	ssScore << " - SCORE: " << this->points;
	this->scoreText.setString(ssScore.str());
	ssText << " - Level: " << this->level;
	this->levelText.setString(ssText.str());
	//Update player HPBar
	float hpPercent = static_cast<float>(this->ship->getHp()) / this->ship->getHpMax();
	this->playerHpBar.setPosition(this->ship->getPos().x - 25, this->ship->getPos().y - 25);
	this->playerHpBarBack.setPosition(this->ship->getPos().x - 25, this->ship->getPos().y - 25);
	this->playerHpBar.setSize(sf::Vector2f(100.f * hpPercent, this->playerHpBar.getSize().y));
	//Update boss HPBar
	if (this->boss != nullptr && this->level >= 4) {
		float bossHpPercent = static_cast<float>(this->boss->getHP()) / this->boss->getHPMax();
		this->bossHpBar.setPosition(this->boss->getPosition().x, this->boss->getPosition().y - 25);
		this->bossHpBarBack.setPosition(this->boss->getPosition().x, this->boss->getPosition().y - 25);
		this->bossHpBar.setSize(sf::Vector2f(150.f * bossHpPercent, this->bossHpBar.getSize().y));
	}
}
void Game::updateCollision() {
	//Left world collision
	if (this->ship->getBounds().left < 0.0f) {
		this->ship->setPosition(0.f, this->ship->getBounds().top);
	}
	//Right world collision
	else if (this->ship->getBounds().left + this->ship->getBounds().width >= this->window->getSize().x) {
		this->ship->setPosition(this->window->getSize().x - this->ship->getBounds().width, this->ship->getBounds().top);
	}
	//Top world collision
	if (this->ship->getBounds().top < 0.0f) {
		this->ship->setPosition(this->ship->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->ship->getBounds().top + this->ship->getBounds().height >= this->window->getSize().y) {
		this->ship->setPosition(this->ship->getBounds().left, this->window->getSize().y - this->ship->getBounds().height);
	}
}
//---------------------Render----------------------//
void Game::renderWorld() {
	this->window->draw(this->worldBackGround);
}
void Game::renderGui(sf::RenderTarget* target) {
	target->draw(this->scoreText);
	target->draw(this->playerHpBarBack);
	target->draw(this->levelText);
	target->draw(this->playerHpBar);
	if (this->level >= 4) {
		target->draw(this->bossHpBarBack);
		target->draw(this->bossHpBar);
	}
}
void Game::render() {
	this->window->clear(sf::Color(255, 255, 255, 255));
	//Draw Background
	this->renderWorld();
	this->ship->render(*this->window);
	for (auto* armo : this->armos) {
		armo->render(*this->window);
	}
	if (this->boss != nullptr)
	{
		for (auto* bi : this->bloodItems) {
			bi->render(*this->window);
		}
	}
	this->renderGui(this->window);
	//Render Chicken
	for (Chicken* chicken : chickens) {
		chicken->render(this->window);
	}
	//Render eggs
	for (auto* i : this->eggs)
	{
		i->render(this->window);
	}
	//Game thua
	if (this->ship->getHp() <= 0)
	{
		if (hcMenu->isHighscore(this->points) && writeAble == true)
		{
			hcMenu->updateHighscores(this->points);
			writeAble = false;
			hcMenu->initHighscores(this->window->getSize().x, this->window->getSize().y);
		}
		this->window->draw(this->gameOverText);
		gameStatus = 1;
	}
	//Game thang
	if (this->boss == nullptr)
	{
		if (hcMenu->isHighscore(this->points) && writeAble == true)
		{
			hcMenu->updateHighscores(this->points);
			writeAble = false;
			hcMenu->initHighscores(this->window->getSize().x, this->window->getSize().y);
		}
		this->window->draw(this->winText);
		gameStatus = 2;
	}
	//Render Boss
	if (level >= 4) {
		if (this->boss != nullptr) {
			this->boss->render(*this->window);
			//Render egg for boss
			for (auto* i : this->bossEggs1)
			{
				i->render(this->window);
			}
			for (auto* i : this->bossEggs2)
			{
				i->render(this->window);
			}
			for (auto* i : this->bossEggs3)
			{
				i->render(this->window);
			}
		}
	}
	this->window->display();
}
void Game::update() {
	//code
	this->updateCollision();
	this->updateArmos();
	this->ship->update();
	this->updateBloodItems();
	this->updateGui();
	this->updateChicken(this->level);
	//neu level 2, 3 thi khong cho tha trung
	//if (this->level != 3 && this->level != 2) {
	this->updateEgg();
	for (auto* egg : eggs) {
		egg->moveVertical();
	}
	//}
	//Boss------------------------
	if (level >= 4 && this->boss != nullptr) {
		for (auto* egg : bossEggs1) {
			egg->bossShoot1();
		}
		for (auto* egg : bossEggs2) {
			egg->bossShoot2();
		}
		for (auto* egg : bossEggs3) {
			egg->bossShoot3();
		}
		this->updateBoss();
	}
	//----------------------
	this->collisionEggChicken();
	///Check level moi
	if (this->chickens.empty() && this->isBossLevel == false)
	{
		this->level += 1;
		for (int i = 0; i < this->eggs.size(); ++i)
		{
			this->eggs.erase(this->eggs.begin() + i);
		}
		//đếm giờ level 3
		if (level == 3) {
			clock.restart();
			//xoa giay thua (van chua duoc)
			for (int i = 0; i < this->eggs.size(); ++i)
			{
				this->eggs.erase(this->eggs.begin() + i);
			}
		}
		initChicken(level);
		updateChicken(level);
	}
	this->collisionChickenShip();
	this->collisionShipHpItem();
	if (this->level == 4)
	{
		isBossLevel = true;
	}
}
Game::Game(void)
{
	this->initVariable();
	this->initWindow();
	this->initShip();
	this->initArmo();
	this->initWorld();
	this->initSound();
	this->initGui();
	this->initChicken(this->level);
	this->initEggs();
	this->initBoss();
}
Game::~Game(void)
{
	delete this->window;
	delete this->ship;
	delete this->boss;
	//Delete Texture
	for (auto& i : this->textures) {
		delete i.second;
	}
	//Delete Armo
	for (auto& i : this->armos) {
		delete i;
	}
	//Delete Chickens
	for (auto* i : this->chickens)
	{
		delete i;
	}
	//Delete Eggs
	for (auto* i : this->eggs)
	{
		delete i;
	}
	for (auto* i : this->bloodItems)
	{
		delete i;
	}
}
void Game::initChicken(int level)
{
	while (chickens.size() > 0) {
		chickens.pop_back();
	}
	int numChickensCol = 4;
	int numChickensRow = 10;
	if (level == 1)
	{
		numChickensCol = 4;
		numChickensRow = 10;
		float spacing = 100.0f; // Khoảng cách giữa các con gà
		sf::Vector2f chickenPosition;
		chickenPosition.x = (1600 - numChickensCol * spacing) / 2; // Vị trí x của con gà
		chickenPosition.y = 50.f;
		for (int i = 0; i < numChickensRow; i++) {
			for (int j = 0; j < numChickensCol; j++) {
				sf::Vector2f position = chickenPosition + sf::Vector2f(i * spacing, j * spacing);
				Chicken* chicken = new Chicken(this->textures["CHICKEN"], position.x, position.y); // Tạo con gà mới
				chickens.push_back(chicken);
			}
		}
	}
	if (level == 2)
	{
		int rows = 8;
		int columns = 8;
		float spacingX = 80.0f;
		float spacingY = 60.0f;
		float screenWidth = 1600;
		float screenHeight = 900;
		float triangleWidth = columns * spacingX - (spacingX / 2.0f);
		float startX = (screenWidth - triangleWidth) / 2.0f;
		float startY = 50.0f;
		for (int row = 0; row < rows; row++) {
			int chickenslnRow = columns - row;
			float rowStartX = startX + (row * spacingX / 2.0f);
			for (int column = 0; column < chickenslnRow; column++) {
				float chickenX = rowStartX + (column * spacingX);
				float chickenY = startY + (row * spacingY);
				Chicken* chicken = new Chicken(this->textures["CHICKEN"], chickenX, chickenY); // Tạo con gà mới
				chickens.push_back(chicken);
			}
		}
	}
	if (level == 3)
	{
		int numChickenLv3 = 7;
		for (int i = 0; i < numChickenLv3; i++) {
			sf::Vector2f chickenPosition;
			randX = std::rand() % 700 + 900;
			randY = std::rand() % 200;
			Chicken* chicken = new Chicken(this->textures["METEORITE"], randX, randY);
			chicken->p = 0;
			chickens.push_back(chicken);
		}
		for (int i = 0; i < numChickenLv3; i++) {
			sf::Vector2f chickenPosition;
			randX = std::rand() % 700;
			randY = std::rand() % 200;
			Chicken* chicken = new Chicken(this->textures["METEORITE"], randX, randY);
			chicken->p = 1;
			chickens.push_back(chicken);
		}
	}
}
void Game::updateChicken(int level)
{
	int numRows;
	int numCols;
	int chickenIndex;
	if (level == 1) {
		numRows = 10;
		numCols = 4;
		chickenIndex = 0;
		for (int i = 0; i < chickens.size(); i++) {
			chickens[i]->moveHorizontal();
		}
	}
	if (level == 2)
	{
		int rows = 8;
		int columns = 8;
		chickenIndex = 0;
		for (int i = 0; i < chickens.size(); i++) {
			chickens[i]->moveVertical();
		}
	}
	if (level == 3)
	{
		for (int i = 0; i < chickens.size(); i++) {
			chickens[i]->moveMeteorite();
		}
		//sau 30s qua man
		if (clock.getElapsedTime().asSeconds() >= 20) {
			for (int i = 0; i < chickens.size(); i++) {
				this->chickens.erase(this->chickens.begin() + i);
			}
		}
	}
}
void Game::initEggs() {
	Egg* egg = new Egg(0.0f, 0.f);
}
void Game::updateMousePosition() {
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition();
	// convert it to world coordinates
	sf::Vector2f worldPos = this->window->mapPixelToCoords(pixelPos);
	this->ship->move(worldPos.x - 200, worldPos.y - 200);
}
void Game::updateEgg()
{
	dropEggTimer += 0.4f;
	// Kiểm tra nếu đã đạt đến ngưỡng thời gian thả trứng
	if (dropEggTimer >= dropEggThreshold) {
		if (chickens.size() > 0)
		{
			int randomChickenIndex = rand() % chickens.size();
			Chicken* randomChicken = chickens[randomChickenIndex];
			eggs.push_back(new Egg(randomChicken->getPosition().x, randomChicken->getPosition().y)); // Thực hiện thả trứng
			dropEggTimer = 0.0f; // Đặt lại thời gian đếm về 0
		}
	}
	//Check colision between egg and ship
	for (int i = 0; i < this->eggs.size(); ++i)
	{
		if (eggs[i]->getBounds().intersects(this->ship->getBounds()))
		{
			soundBonk.play();
			delete this->eggs[i];
			this->eggs.erase(this->eggs.begin() + i);
			this->ship->loseHp(1);
		}
	}
}
//Collision armo voi chicken
void Game::collisionEggChicken()
{
	for (int i = 0; i < this->chickens.size(); ++i)
	{
		bool chicken_removed = false;
		for (size_t k = 0; k < this->armos.size() && chicken_removed == false; ++k)
		{
			if (this->armos[k]->getBounds().intersects(this->chickens[i]->getBounds()))
			{
				soundChickenKilled.play();
				this->armos.erase(this->armos.begin() + k);
				//level 3 khong ban duoc thien thach
				if (level != 3) this->chickens[i]->loseHp(1);
				if (chickens[i]->HP <= 0)
				{
					this->chickens.erase(this->chickens.begin() + i);
				}
				// cong diem
				this->points += 20;
				chicken_removed = true;
			}
		}
	}
}
void Game::collisionChickenShip()
{
	for (int i = 0; i < this->chickens.size(); ++i)
	{
		if (chickens[i]->getBounds().intersects(this->ship->getBounds()))
		{
			this->soundExplosion.play();
			this->chickens.erase(this->chickens.begin() + i);
			this->ship->loseHp(1);
		}
	}
}
void Game::collisionShipHpItem()
{
	for (int i = 0; i < this->bloodItems.size(); ++i) {
		if (bloodItems[i]->getBounds().intersects(this->ship->getBounds()))
		{
			this->soundHarry.play();
			this->bloodItems.erase(this->bloodItems.begin() + i);
			this->points += 50;
			this->ship->loseHp(-1);
		}
	}
}
void Game::updateBoss()
{
	this->boss->appear();
	for (int i = 0; i < this->armos.size(); ++i)
	{
		if (armos[i]->getBounds().intersects(this->boss->getBounds()))
		{
			soundBonk.play();
			this->armos.erase(this->armos.begin() + i);
			this->boss->loseHP(1);
			this->points += 12;
		}
	}
	float randomPosX = rand() % 100;
	int currentHP = this->boss->getHP();
	this->boss->moveBoss();
	dropEggTimerBoss += 0.4f;
	if (dropEggTimerBoss >= dropEggThresholdBoss)
	{
		if (currentHP >= 0)
		{
			Egg* egg1 = new Egg(this->textures["CUP"], this->boss->getPosition().x, this->boss->getPosition().y);
			bossEggs1.push_back(egg1);
			egg1->bossShoot1();
			Egg* egg2 = new Egg(this->textures["CUP"], this->boss->getPosition().x, this->boss->getPosition().y);
			bossEggs2.push_back(egg2);
			egg2->bossShoot2();
			Egg* egg3 = new Egg(this->textures["CUP"], this->boss->getPosition().x, this->boss->getPosition().y);
			bossEggs3.push_back(egg3);
			egg3->bossShoot3();
			dropEggTimerBoss = 0.0f;
		}
		else {
			delete this->boss;
			this->isBossLevel = false;
			this->bossHpBar.setPosition(sf::Vector2f(-100.f, -100.f));
			this->bossHpBarBack.setPosition(sf::Vector2f(-100.f, -100.f));
			this->boss = nullptr;
		}
	}
	for (int i = 0; i < this->bossEggs1.size(); ++i)
	{
		if (bossEggs1[i]->getBounds().intersects(this->ship->getBounds()))
		{
			soundAnkara.play();
			this->bossEggs1.erase(this->bossEggs1.begin() + i);
			this->ship->loseHp(2);
		}
	}
	for (int i = 0; i < this->bossEggs2.size(); ++i)
	{
		if (bossEggs2[i]->getBounds().intersects(this->ship->getBounds()))
		{
			soundAnkara.play();
			this->bossEggs2.erase(this->bossEggs2.begin() + i);
			this->ship->loseHp(2);
		}
	}
	for (int i = 0; i < this->bossEggs3.size(); ++i)
	{
		if (bossEggs3[i]->getBounds().intersects(this->ship->getBounds()))
		{
			soundAnkara.play();
			this->bossEggs3.erase(this->bossEggs3.begin() + i);
			this->ship->loseHp(2);
		}
	}
	if (this->boss != nullptr)
	{
		if (clockBossShip.getElapsedTime().asSeconds() >= 3) {
			if (this->boss->getBounds().intersects(this->ship->getBounds()))
			{
				this->ship->loseHp(1);
				clockBossShip.restart();
				soundBonk.play();
			}
		}
	}
}
void Game::restart() {
	this->points = 0;
	this->level = 1;
	gameStatus = 0;
	//hcMenu->loadFromText();
	this->ship->setHp(this->ship->getHpMax());
	for (int i = 0; i < chickens.size(); i++) {
		this->chickens.erase(this->chickens.begin() + i);
	}
	initChicken(level);
	initBoss();
}