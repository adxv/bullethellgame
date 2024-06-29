#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Player
{
private:
	CircleShape shape;
	float movementSpeed;

	void initVariables();
	void initShape();

public:

	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//accessors
	const CircleShape& getShape() const;
	
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);

};

