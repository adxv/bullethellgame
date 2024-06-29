#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Drawable.hpp>

using namespace sf;

class Projectile
{
private:
	CircleShape shape;
	float projectileSpeed;
	float projectileSize;
	Vector2f direction;

	void initVariables();
	void initShape(const Vector2f& position);

public:

	Projectile(const Vector2f& position, const Vector2f& direction);
	virtual ~Projectile();

	//accessors
	FloatRect getGlobalBounds() const;
	const CircleShape& getShape() const;
	float getProjectileSpeed() const;

	//mutators
	void setProjectileSpeed(float speed);

	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};

