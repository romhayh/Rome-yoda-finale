#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "math_functions.hpp"
#include "player.hpp"
#include "bot.hpp"

extern Player* players;
extern Bot* bots;
extern int state;

Player::Player() {
	this->name = '/0';
	this->color = sf::Color(105, 10, 0);
	this->position = sf::Vector2f(10000, 10000);
	this->movement = sf::Vector2f(0, 0);

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);
	this->circle.setPosition(this->position);

	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->score = 0;
}

Player::Player(sf::Color&& color, std::string&& name, const sf::Vector2f& position) {
	//properties:
	this->name = name;
	this->color = color;
	this->position = position;
	this->movement = sf::Vector2f(1.5f, 1.5f);

	//graphics
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);//pinning the origin to the middle of the circle
	this->circle.setPosition(this->position);

	//collision

	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = false;

	this->score = 0;
}

Player::Player(Player&& other) {
	std::cout << name << " was copied!!"<< std::endl;

	//properties:
	this->name = other.name;
	this->color = other.color;
	this->position = other.position;
	this->movement = other.movement;

	//graphics
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);			 //pinning the origin to the middle of the circle
	this->circle.setPosition(this->position);

	//collision
	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = other.alive;

	this->score = other.score;
}

Player::Player(const Player& other) {
	std::cout << name << " was copied!!" << std::endl;

	//properties:
	this->name = other.name;
	this->color = other.color;
	this->position = other.position;
	this->movement = other.movement;

	//graphics
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);			 //pinning the origin to the middle of the circle
	this->circle.setPosition(this->position);

	//collision
	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = other.alive;

	this->score = other.score;
}

Player& Player::operator=(Player&& other) {
	//properties:
	this->name = other.name;
	this->color = other.color;
	this->position = other.position;
	this->movement = other.movement;

	//graphics
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);			 //pinning the origin to the middle of the circle
	this->circle.setPosition(this->position);

	//collision
	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = other.alive;
	
	this->score = other.score;

	std::cout << name << " was constructed"<< std::endl;

	return *this;
}

Player& Player::operator=(const Player& other) {
	//properties:
	this->name = other.name;
	this->color = other.color;
	this->position = other.position;
	this->movement = other.movement;

	//graphics
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4, 4);			 //pinning the origin to the middle of the circle
	this->circle.setPosition(this->position);

	//collision
	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = other.alive;

	this->score = other.score;

	return *this;
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(this->left)) {
		rotate(this->movement, -this->angle);
	}
	else if (sf::Keyboard::isKeyPressed(this->right)) {
		rotate(this->movement, this->angle);
	}
	this->circle.setPosition(this->position);
	this->circle.move(this->movement);
	this->position = this->circle.getPosition();
}

int index{ 0 };

void Player::init_position()
{
	bool oqupied{ false };

	if (state < 4) {
		index = (int)(std::rand() % P_LENGTH);

		for (int i = 0; i < 5; i++) {
			if (players[i].position == positions[index]) {
				oqupied = true;
			}
		}
		if (oqupied) {
			this->init_position();
		}
		else {
			this->position = positions[index];
		}
	}
	else {
		index = (int)(std::rand() % P_LENGTH);

		for (int i = 0; i < 2; i++) {
			if (players[i].position == positions[index]) {
				oqupied = true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (bots[i].getPosition() == positions[index]) {
				oqupied = true;
			}
		}
		if (oqupied) {
			this->init_position();
		}
		else {
			this->position = positions[index];
		}
	}
}
void Player::set_controls(sf::Keyboard::Key&& left, sf::Keyboard::Key&& right) {
	this->left = left;
	this->right = right;
	this->def_left = true;
	this->def_right = true;
}

void Player::erase_left()
{
	this->left = UNKNOWN;
	this->def_left = false;
}

void Player::erase_right()
{
	this->right = UNKNOWN;
	this->def_right = false;
}


Player::~Player() {
	std::cout << this->name << " was destructed" << std::endl;
}
extern Player* players;
const unsigned int count_players_alive()
{
	unsigned int count{ 0 };
	for (int i = 0; i < 5; i++) {
		if (players[i].has_left() && players[i].has_right() && players[i].alive) {
			count++;
		}
	}
	return count;
}



const unsigned int count_players_init()
{
	unsigned int pi{ 0 }; // pi standes for players initialized
	for (int i{ 0 }; i < 5; i++) {
		if (players[i].def_left && players[i].def_right) {
			pi++;
		}
	}
	return pi;
}
