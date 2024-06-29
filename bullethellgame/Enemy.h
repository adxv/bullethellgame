#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Enemy
{
private:
	CircleShape shape;
	Vector2f velocity;
	//int type;
	//float movementSpeed;

	void initVariables();
	void initShape();

public:

	Enemy(const Vector2f& position, const Vector2f& initialVelocity = Vector2f(0.f, 0.f));
	virtual ~Enemy();

	//accessors
	CircleShape& getShape();
	Vector2f getVelocity() const;

	//void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);

};

