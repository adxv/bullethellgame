#include "Projectile.h"

void Projectile::initVariables()
{
	this->projectileSpeed = 1.f;
	this->projectileSize = 7.f;
}

void Projectile::initShape(const Vector2f& position)
{
	this->shape.setFillColor(Color::Red);
	this->shape.setOutlineColor(Color::Yellow);
	this->shape.setOutlineThickness(2.f);
	this->shape.setRadius(projectileSize);
	this->shape.setPosition(position);

	//this->shape.setPosition(Vector2f(
	//	static_cast<float>(rand() % w.getSize().x - this->shape.getGlobalBounds().width),
	//	static_cast<float>(rand() % w.getSize().y - this->shape.getGlobalBounds().height)));
}

FloatRect Projectile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}
const CircleShape& Projectile::getShape() const
{
	return this->shape;
}

float Projectile::getProjectileSpeed() const
{
	return this->projectileSpeed;
}

Projectile::Projectile(const Vector2f& position, const Vector2f& direction) : direction(direction)
{
	this->initShape(position);
	this->initVariables();
}

Projectile::~Projectile()
{
}

void Projectile::setProjectileSpeed(float speed)
{
	this->projectileSpeed = speed;
}

void Projectile::update(const RenderTarget* target)
{
	this->shape.move(this->direction * this->projectileSpeed);
}

void Projectile::render(RenderTarget* target)
{
	target->draw(this->shape);
}


