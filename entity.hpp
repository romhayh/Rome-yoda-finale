#pragma once
#include <iostream>
#include <array>
#include <string>

#include "math_functions.hpp"
#include "constants.hpp"


class Entity {
protected:
	std::string name;
	sf::Vector2f position;
	sf::Vector2f movement;
	sf::Color color;
	const float angle = 0.07f;
	sf::CircleShape circle;

	bool alive = true;
	std::array<sf::Vector2f, 4> last_steps;
	unsigned int score{ 0 };

public:
	Entity(){}
	Entity(const Entity& other);
	Entity& operator= (const Entity& other);
	Entity(Entity&& other);
	Entity& operator= (Entity&& other);

public:
	// collision and movement
	virtual void move() {}
	const bool isAlive() const;
	void update_last_steps();
	virtual bool collision_check();
	virtual void collision() {}

public:
	//getters and setters

	void setPosition(sf::Vector2f&& position);
	void setPosition(const sf::Vector2f& position);
	virtual void init_position() {};

	const sf::Vector2f& getPosition() const;
	//	^~~~~ the function will not change what it gives
	const sf::CircleShape& get_circle() const;
	//	the funtion will not change the	obj ~~~~^ 	
	const std::array<sf::Vector2f, 4>& get_last_steps() const;

	void set_movement(const sf::Vector2f& v);

	void init_movement();

	std::string get_name();
	
	const sf::Color get_color() const;

	void set_score(const unsigned int& score);
	void inc_score();
	unsigned int get_score();
	void raise();
	void kill();

};