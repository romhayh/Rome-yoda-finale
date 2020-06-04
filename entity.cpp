#include "entity.hpp"

extern std::vector<sf::Vector2f> marked;

Entity::Entity(const Entity & other)
{
	this->name = other.name;
	this->circle = other.circle;
	this->circle.setOrigin(4.f, 4.f);
	this->color = other.color;
	this->circle.setFillColor(this->color);

	this->position = other.position;
	this->movement = other.movement;
	
	for (int i = 0; i < 4; i++) {
		this->last_steps[i] = other.last_steps[i];
	}
	this->alive = other.alive;
	this->score = other.score;
}

Entity & Entity::operator=(const Entity & other)
{
	this->name = other.name;
	this->circle = other.circle;
	this->circle.setOrigin(4.f, 4.f);
	this->color = other.color;
	this->circle.setFillColor(this->color);

	this->position = other.position;
	this->movement = other.movement;

	for (int i = 0; i < 4; i++) {
		this->last_steps[i] = other.last_steps[i];
	}
	this->alive = other.alive;
	this->score = other.score;
	return *this;
}

Entity::Entity(Entity && other)
{
	this->name = other.name;
	this->circle = other.circle;
	this->circle.setOrigin(4.f, 4.f);
	this->color = other.color;
	this->circle.setFillColor(this->color);

	this->position = other.position;
	this->movement = other.movement;

	for (int i = 0; i < 4; i++) {
		this->last_steps[i] = other.last_steps[i];
	}
	this->alive = other.alive;
	this->score = other.score;
}


Entity & Entity::operator=(Entity && other)
{
	
	this->name = other.name;
	this->circle = other.circle;
	this->circle.setOrigin(4.f, 4.f);
	this->color = other.color;
	this->circle.setFillColor(this->color);

	this->position = other.position;
	this->movement = other.movement;

	for (int i = 0; i < 4; i++) {
		this->last_steps[i] = other.last_steps[i];
	}
	this->alive = other.alive;
	this->score = other.score;
	return *this;
}

const bool Entity::isAlive() const
{
	return this->alive;
}

void Entity::update_last_steps()
{

	this->last_steps[3] = this->last_steps[2];
	this->last_steps[2] = this->last_steps[1];
	this->last_steps[1] = this->last_steps[0];
	this->last_steps[0] = this->position;

	marked.reserve(1);
	marked.emplace_back(this->position.x, this->position.y);
}

bool Entity::collision_check()
{

	using namespace sf;
	const auto& pos = this->position;

	if (pos.x >= WIDTH - 4) {
		std::cout << "collided with the right wall" << std::endl;
		return true;
	}

	if (pos.y >= HEIGHT - 4) {
		std::cout << "collided with the buttom wall" << std::endl;
		return true;
	}

	if (pos.x <= 4) {
		std::cout << "collided with the left wall" << std::endl;
		return true;
	}

	if (pos.y <= 4) {
		std::cout << "collided with the upper wall" << std::endl;
		return true;
	}


	bool steped_on = false;

	for (Vector2f v : marked) {
		for (Vector2f p : this->last_steps) {
			if (p == v) steped_on = true;

		}
		if (distance(v, pos) < 8.f && !steped_on) {

			std::cout << pos << " collided with " << v << std::endl;
			return true;
		}
	}

	return false;
}


void Entity::setPosition(sf::Vector2f&& position) {
	this->position = position;
}
void Entity::setPosition(const sf::Vector2f& position)
{
	if (position.x < WIDTH && position.y < HEIGHT) {
		this->position = position;
	}
}
const sf::Vector2f& Entity::getPosition() const {
	return this->position;
}
const sf::CircleShape& Entity::get_circle() const {
	return this->circle;
}
const std::array<sf::Vector2f, 4>& Entity::get_last_steps() const {
	return this->last_steps;
}
void Entity::set_movement(const sf::Vector2f& v) {

	this->movement = v;
	normalize(this->movement, 2.25);

}

void Entity::init_movement() {
	using namespace sf;
	Vector2f v((WIDTH / 2) - this->position.x, (HEIGHT / 2) - this->position.y);
	normalize(v, 2.25);
	this->movement = v;
}

std::string Entity::get_name()
{
	return this->name;
}

const sf::Color Entity::get_color() const
{
	return this->color;
}



void Entity::set_score(const unsigned int & score)
{
	this->score = score;
}

void Entity::inc_score()
{
	++this->score;
}

unsigned int Entity::get_score()
{
	return this->score;
}

void Entity::raise()
{
	this->alive = true;
}

void Entity::kill()
{
	this->alive = false;
}


