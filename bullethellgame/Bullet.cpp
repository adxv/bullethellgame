#include "Bullet.h"

void Bullet::initVariables()
{
	this->bulletSpeed = 5.f;
}

void Bullet::initShape(const Vector2f& position)
{
	this->shape.setFillColor(Color::White);
	this->shape.setSize(Vector2f(3.f, 20.f));
	this->shape.setPosition(position);

	//this->shape.setPosition(Vector2f(
	//	static_cast<float>(rand() % w.getSize().x - this->shape.getGlobalBounds().width),
	//	static_cast<float>(rand() % w.getSize().y - this->shape.getGlobalBounds().height)));
}

FloatRect Bullet::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

Bullet::Bullet(const Vector2f& position)
{
	this->initShape(position);
	this->initVariables();
}

Bullet::~Bullet()
{
}

void Bullet::update(const RenderTarget* target)
{
	this->shape.move(0.f, -bulletSpeed);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shape);
}


