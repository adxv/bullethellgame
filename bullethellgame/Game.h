#pragma once

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

#include "Player.h"
#include "Bullet.h"
#include "Projectile.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;


class Game
{
private:
	VideoMode vm;
	RenderWindow* w;
	Event e;
	bool endGame;
	void checkCollisions();


	Player player;
	//Bullet bullet;
	std::vector<Bullet> Bullets;
	std::vector<Projectile> Projectiles;
	std::vector<Enemy> Enemies;

	//player bullets
	float spawnTimerM;
	float spawnTimer;
	int maxBullets;
	int shotCount;

	//enemy projectiles
	float spawnTimerMP;
	float spawnTimerP;
	int projectileSpawnAmount;
	int maxProjectiles;
	int projectileCount;
	float rotationAngle;

	//enemy properties
	float enemySpeed;
	int enemyDirection;

	void incrementRotation();

	void initVariables();
	void initWindow();

public:
	//constructor destructor
	Game();

	~Game();

	//accessors

	//modifiers

	//functions
	const bool running() const;
	void pollEvents();
	static bool isColliding(const CircleShape& shape1, const CircleShape& shape2);
	static void simpleMoveFunction(CircleShape& shape, RenderWindow* window, float speed, const Vector2f& destination);

	void spawnBullets();
	void deleteBullets();

	void spawnProjectiles();
	void deleteProjectiles();

	void spawnEnemies();
	void coastEnemy(Enemy& enemy);
	//void killEnemies();

	

	void update();
	void render();
};

