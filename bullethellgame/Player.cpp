#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 2.f;
}

void Player::initShape()
{
	this->shape.setFillColor(Color::White);
	this->shape.setRadius(10.f);
	this->shape.setPosition(512.f, 720.f);
}

Player::Player(float x, float y) {
	this->initShape();
	this->initVariables();
}

Player::~Player() {
	
}


void Player::updateInput()
{
	//keyboard input
	if (!Keyboard::isKeyPressed(Keyboard::LShift)) {
		this->movementSpeed = 2.f;
		this->shape.setFillColor(Color::White);
		if (Keyboard::isKeyPressed(Keyboard::Left)) { this->shape.move(-this->movementSpeed, 0.f); }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { this->shape.move(this->movementSpeed, 0.f); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { this->shape.move(0.f, -this->movementSpeed); }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { this->shape.move(0.f, this->movementSpeed); }
	}
	else {
		this->movementSpeed = 1.f;
		this->shape.setFillColor(Color(127, 127, 127, 255));
		if (Keyboard::isKeyPressed(Keyboard::Left)) { this->shape.move(-this->movementSpeed, 0.f); }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { this->shape.move(this->movementSpeed, 0.f); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { this->shape.move(0.f, -this->movementSpeed); }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { this->shape.move(0.f, this->movementSpeed); }
	}


}
const CircleShape& Player::getShape() const
{
	return this->shape;
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	
	//player radius = 10

	if (this->shape.getGlobalBounds().left <= 2.f) {
		shape.setPosition(2.f, this->shape.getGlobalBounds().top);
	}
	
	else if (this->shape.getGlobalBounds().left + 20.f >= target->getSize().x-2.f) {
		shape.setPosition(target->getSize().x - 20.f-2.f, this->shape.getGlobalBounds().top);
	}

	if (this->shape.getGlobalBounds().top <= 0.f) {
		shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}

	else if (this->shape.getGlobalBounds().top + 20.f >= target->getSize().y) {
		shape.setPosition(this->shape.getGlobalBounds().left ,target->getSize().y - 20.f);
	}

}

void Player::update(const RenderTarget* target)
{
	
	this->updateInput();
	this->updateWindowBoundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(this->shape);
}
