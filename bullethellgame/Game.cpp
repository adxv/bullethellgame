#include "Game.h"

//todo	- make player and enemy spawn position independent from window size
//		- add background and foreground image
//		- make the game vertical, with the hud on the right side and gameplay on the left side
//		- implement score system
//		- implement enemy types

//done
//		- implement enemy movement

float deg2rad(float degrees)
{
	return degrees * 3.14159f / 180.f;
}

void Game::initVariables()
{
	this->endGame = false;

	//player bullets
	this->spawnTimerM = 10.f;
	this->spawnTimer = this->spawnTimerM;
	this->maxBullets = 40;
	this->shotCount = 0;

	//enemy projectiles
	this->spawnTimerMP = 50.f;
	this->spawnTimerP = this->spawnTimerM;
	this->projectileSpawnAmount = 24;
	this->maxProjectiles = 255;
	this->projectileCount = 0;
	this->rotationAngle = 0.f;

	//enemy properties
	this->enemySpeed = 0.3;
	this->enemyDirection = 0;
}

void Game::initWindow()
{
	this->vm = VideoMode(1024, 768);
	this->w = new RenderWindow(this->vm, "bullethellgame", Style::Close | Style::Titlebar);
	this->w->setFramerateLimit(200);
}

//constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
}

//destructor
Game::~Game()
{
	delete this->w;
}

const bool Game::running() const
{
	return this->w->isOpen();
}

void Game::pollEvents()
{
	while (this->w->pollEvent(this->e)) {
		switch (this->e.type) {
		case Event::Closed:
			this->w->close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape) {
				this->w->close();
			break;

			}
		}
	}
}

void Game::spawnEnemies()
{
		if (this->Enemies.size() < 1) {

			Vector2f enemyPosition;

			this->Enemies.push_back(Enemy(enemyPosition));
		}
}

void Game::coastEnemy(Enemy& enemy)
{
	Vector2f screenSize = this->w->getView().getSize();
	CircleShape& shape = enemy.getShape();
	Vector2f currentPosition = shape.getPosition();
	Vector2f destination;

	if (currentPosition.x <= 0.f) {
		enemyDirection = 1; //move right
	}
	else if (currentPosition.x >= screenSize.x - shape.getRadius() * 2.f) {
		enemyDirection = -1; //move left
	}

	if (enemyDirection == 1) {
		//move rightwards
		destination = Vector2f(screenSize.x - shape.getRadius() * 2.f, currentPosition.y);
	}
	else {
		//move leftwards
		destination = Vector2f(0.f, currentPosition.y);
	}

	simpleMoveFunction(shape, this->w, enemySpeed, destination);
}



void Game::spawnBullets()
{

	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		if (this->spawnTimer < this->spawnTimerM) {
			this->spawnTimer += 1.f;
		}
		else {
			if (this->Bullets.size() < this->maxBullets) {

				Vector2f playerPosition = this->player.getShape().getPosition();
				Vector2f bulletPosition;

				if (shotCount % 2 == 0) {
					bulletPosition = playerPosition + Vector2f(this->player.getShape().getGlobalBounds().width+13.f, -20.f);
				}
				else {
					bulletPosition = playerPosition + Vector2f(-this->player.getShape().getGlobalBounds().width+3.f, -20.f);
				}

				this->Bullets.push_back(Bullet(bulletPosition));
				this->shotCount++;
				this->spawnTimer = 0.f;
			}
		}
	}
}

void Game::deleteBullets()
{
	//get window bounds
	FloatRect windowBounds(0.f, 0.f, this->w->getSize().x, this->w->getSize().y);

	this->Bullets.erase(
		std::remove_if(this->Bullets.begin(), this->Bullets.end(), [&windowBounds](Bullet& bullet) {
			return !windowBounds.intersects(bullet.getGlobalBounds());
			}),
		this->Bullets.end()
	);
}


void Game::spawnProjectiles()
{
	Enemy& enemy = this->Enemies[0];
	Vector2f enemyPosition = enemy.getShape().getPosition();

	float angleIncrement = 360.f / projectileSpawnAmount;

	if (this->spawnTimerP < this->spawnTimerMP) {
		this->spawnTimerP += 1.f;
	}
	else {
		if (this->Projectiles.size() < this->maxProjectiles) {
			float angle = this->rotationAngle;
			if (enemyDirection == 1) {
				angle += 180.f;
			}

			for (int i = 0; i < projectileSpawnAmount; ++i)
			{
				Vector2f direction(std::cos(deg2rad(angle)), std::sin(deg2rad(angle)));

				this->Projectiles.push_back(Projectile(enemyPosition, direction));
				angle += angleIncrement;
			}
			this->projectileCount++;
			this->spawnTimerP = 0.f;
		}
	}
}


void Game::deleteProjectiles()
{
	//get window bounds
	FloatRect windowBounds(0.f, 0.f, this->w->getSize().x, this->w->getSize().y);

	this->Projectiles.erase(
		std::remove_if(this->Projectiles.begin(), this->Projectiles.end(), [&windowBounds](Projectile& projectile) {
			return !windowBounds.intersects(projectile.getGlobalBounds());
			}),
		this->Projectiles.end()
	);
}

bool Game::isColliding(const CircleShape& shape1, const CircleShape& shape2)
{
	float dx = shape1.getPosition().x - shape2.getPosition().x;
	float dy = shape1.getPosition().y - shape2.getPosition().y;
	float distance = std::sqrt(dx * dx + dy * dy);
	float combinedRadii = shape1.getRadius() + shape2.getRadius();

	return distance < combinedRadii;
}

void Game::checkCollisions()
{
	for (auto& projectile : this->Projectiles)
	{
		if (Game::isColliding(this->player.getShape(), projectile.getShape()))
		{
			this->endGame = true;
			std::cout << "game over" << "\n";
		}
	}
}

void Game::incrementRotation()
{
	this->rotationAngle += 1.f;
	if (this->rotationAngle >= 360.f)
	{
		this->rotationAngle -= 360.f;
	}
}

void Game::simpleMoveFunction(CircleShape& shape, RenderWindow* window, float speed, const Vector2f& destination)
{
	Vector2f currentPosition = shape.getPosition();
	Vector2f direction = destination - currentPosition;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude > 0.f) {
		direction /= magnitude;
	}

	Vector2f movement = direction * speed;

	if (std::abs(destination.x - currentPosition.x) <= std::abs(movement.x)
		&& std::abs(destination.y - currentPosition.y) <= std::abs(movement.y)) {
		shape.setPosition(destination);
	}
	else {
		shape.move(movement);
	}

	FloatRect windowBounds(Vector2f(0.f, 0.f), window->getView().getSize());
	if (!windowBounds.contains(shape.getPosition())) {
		shape.setPosition(std::max(windowBounds.left, std::min(windowBounds.left + windowBounds.width, shape.getPosition().x)),
			std::max(windowBounds.top, std::min(windowBounds.top + windowBounds.height, shape.getPosition().y)));
	}
}

void Game::update()
{
	this->pollEvents();
	this->player.update(this->w);

	this->spawnEnemies();
	for (auto& enemy : this->Enemies)
	{
		this->coastEnemy(enemy);
		enemy.update(this->w);
	}

	this->spawnBullets();
	for (auto& bullet : this->Bullets)
	{
		bullet.update(this->w);
	}
	this->deleteBullets();

	this->spawnProjectiles();
	for (auto& projectile : this->Projectiles)
	{
		projectile.update(this->w);
	}

	this->incrementRotation();

	this->deleteProjectiles();

	this->checkCollisions();
}

void Game::render()
{
	this->w->clear();

	//render
	this->player.render(this->w);

	for (auto& enemy : this->Enemies)
	{
		enemy.render(this->w);
	}
	for (auto& bullet : this->Bullets)
	{
		bullet.render(this->w);
	}
	for (auto& projectile : this->Projectiles)
	{
		projectile.render(this->w);
	}
	

	this->w->display();
}