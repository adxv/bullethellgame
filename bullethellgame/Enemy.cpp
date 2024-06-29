#include "Enemy.h"

void Enemy::initVariables()
{
}

void Enemy::initShape()
{
	this->shape.setFillColor(Color::White);
	this->shape.setRadius(10.f);
	this->shape.setPosition(512.f, 200.f);
}

Enemy::Enemy(const Vector2f& position, const Vector2f& initialVelocity) {
	this->initShape();
	this->initVariables();
}
Enemy::~Enemy() {

}

CircleShape& Enemy::getShape()
{
	return this->shape;
}

Vector2f Enemy::getVelocity() const
{
	return this->velocity;
}

/*

void Enemy::updateWindowBoundsCollision(const sf::RenderTarget* target)
{

	//player radius = 10

	if (this->shape.getGlobalBounds().left <= 2.f) {
		shape.setPosition(2.f, this->shape.getGlobalBounds().top);
	}

	else if (this->shape.getGlobalBounds().left + 20.f >= target->getSize().x - 2.f) {
		shape.setPosition(target->getSize().x - 20.f - 2.f, this->shape.getGlobalBounds().top);
	}

	if (this->shape.getGlobalBounds().top <= 0.f) {
		shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}

	else if (this->shape.getGlobalBounds().top + 20.f >= target->getSize().y) {
		shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - 20.f);
	}

}*/

void Enemy::update(const RenderTarget* target)
{
	//this->updateWindowBoundsCollision(target);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->shape);
}
