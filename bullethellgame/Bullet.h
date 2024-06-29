#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Drawable.hpp>

using namespace sf;

class Bullet
{
private:
	RectangleShape shape;
	float bulletSpeed;

	void initVariables();
	void initShape(const Vector2f& position);

public:

	Bullet(const Vector2f& position);
	virtual ~Bullet();

	//accessors
	FloatRect getGlobalBounds() const; 

	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};

