#include "bot.hpp"
#include "player.hpp"
#include <cstdlib>
#include <ctime>

extern std::vector<sf::Vector2f> marked;
extern int state;
extern Player* players;
extern Bot* bots;

Bot::Bot()
{
	this->color = BLACK;
	this->name = "undefined";
	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(BLACK);
	this->position = { 24242, 424242 };
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(this->position);
	
	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->score = 0;
	this->init = true;
}

Bot::Bot(sf::Color && color, std::string && name, sf::Vector2f && position)
{
	this->color = color;
	this->name = name;
	this->position = position;

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(color);
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(position);

	for (sf::Vector2f& pos : this->last_steps) {
		pos = this->position;
	}

	this->alive = false;

	this->score = 0;
	this->init = true;

}

Bot::Bot(const Bot & other)
{
	this->color = other.color;
	this->name = other.name;
	this->position = other.position;

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(other.color);
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(other.position);

	this->last_steps = other.last_steps;

	this->alive = other.alive;

	this->score = other.score;
	this->init = other.init;
}

Bot & Bot::operator=(const Bot & other)
{
	this->color = other.color;
	this->name = other.name;
	this->position = other.position;

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(other.color);
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(other.position);

	this->last_steps = other.last_steps;

	this->alive = other.alive;

	this->score = other.score;
	this->init = other.init;
	return *this;
}

Bot::Bot(Bot && other)
{
	this->color = other.color;
	this->name = other.name;
	this->position = other.position;

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(other.color);
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(other.position);

	this->last_steps = other.last_steps;

	this->alive = other.alive;

	this->score = other.score;
	this->init = other.init;
}

Bot & Bot::operator=(Bot && other)
{
	this->color = other.color;
	this->name = other.name;
	this->position = other.position;

	this->circle = sf::CircleShape(4.f);
	this->circle.setFillColor(other.color);
	this->circle.setOrigin(4.f, 4.f);
	this->circle.setPosition(other.position);

	this->last_steps = other.last_steps;

	this->alive = other.alive;

	this->score = other.score;
	this->init = other.init;
	return *this;
}

void Bot::move()
{
	this->decide();
	if (this->desicion == LEFT) {
		rotate(this->movement, -this->angle);
	}
	else if (this->desicion == RIGHT) {
		rotate(this->movement, this->angle);
	}
	this->circle.setPosition(this->position);
	this->circle.move(this->movement);
	this->position = this->circle.getPosition();

	this->header_points[0] = this->position + (float)RANGE * this->movement;
	sf::Vector2f temp = this->movement;
	rotate(temp, 11.f * -this->angle); // left
	this->header_points[1] = this->position + (float)RANGE * temp;
	temp = this->movement;
	rotate(temp, 11.f * this->angle); //right
	this->header_points[2] = this->position + (float)RANGE * temp;

	temp = this->movement;
	rotate(temp, 5.5f * -this->angle); // left
	this->header2_points[0] = this->position + (float)(RANGE * 5) * temp;
	temp = this->movement;
	rotate(temp, 5.5f * this->angle); //right
	this->header2_points[1] = this->position + (float)(RANGE * 5) * temp;

	temp = this->movement;
	rotate(temp, -this->angle); // left
	this->header3_points[0] = this->position + (float)(RANGE * 8) * temp;
	temp = this->movement;
	rotate(temp, this->angle); // right
	this->header3_points[1] = this->position + (float)(RANGE * 8) * temp;

	temp = this->movement;
	rotate(temp, -6.8f *this->angle); // left
	this->header3_points[2] = this->position + (float)(RANGE * 10) * temp;

	temp = this->movement;
	rotate(temp, 6.8f * this->angle); // right
	this->header3_points[3] = this->position + (float)(RANGE * 10) * temp;

	this->go_right = 0;
	this->go_left = 0;
	this->go_straight = 0;
	
}

void Bot::collision()
{
	if (this->collision_check()) {
 		this->alive = false;
		for (int i = 0; i < 3; i++) {
			if (bots[i].isAlive() && bots[i].init) {
				bots[i].inc_score();
			}
		}
		for (int i = 0; i < 2; i++) {
			if (players[i].isAlive()) {
				players[i].inc_score();
			}
		}
	}
}


bool Bot::collision_check()
{
	this->bound_check();
	using namespace sf;
	const auto& pos = this->position;
	float angle1 = getAngle(this->movement);
	enum { BOUND = 80 };

	//collision
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
	auto hpos = this->header_points;
	auto hpos2 = this->header2_points;
	auto hpos3 = this->header3_points;

	for (Vector2f v : marked) {

		for (Vector2f p : this->last_steps) {
			if (p == v) steped_on = true;
		}

		if (distance(hpos[1], v) < H_RADIUS + 4.f) { //left
			this->go_right += 3;
			this->go_straight += 3;
		}
		if (distance(hpos[0], v) < H_RADIUS + 4.f) { //straight
			this->go_left += 3;
			this->go_right += 3;
		}
		if (distance(hpos[2], v) < H_RADIUS + 4.f) {//right 
			this->go_left += 3;
			this->go_straight += 3;
		}

		if (distance(hpos2[0], v) < H_RADIUS*3.f + 4.f) { //left
			//header point 2
			this->go_left++;

		}
		if (distance(hpos2[1], v) < H_RADIUS*3.f + 4.f) {//right 
			//header point 2
			this->go_right++;
		}


		//header point 3 check:

		if (distance(hpos[0], v) < H_RADIUS + 4.f) {
			this->go_left++;
		}
		if (distance(hpos[1], v) < H_RADIUS + 4.f) {
			this->go_right++;
		}
		if (distance(hpos[2], v) < H_RADIUS + 4.f) {
			this->go_right++;
			this->go_straight++;
		}
		if (distance(hpos[3], v) < H_RADIUS + 4.f) {
			this->go_left++;
			this->go_straight++;
		}

		if (distance(v, pos) < 8.f && !steped_on) {
			return true;
		}
	}


	return false;
}

int ai_index{ 0 };
void Bot::init_position()
{
	ai_index = (int)(std::rand() % P_LENGTH);
	bool oqupied{ false };
	for (int i = 0; i < 2; i++) {
		if (players[i].getPosition() == positions[ai_index]) {
			oqupied = true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (bots[i].position == positions[ai_index]) {
			oqupied = true;
		}
	}
	if (oqupied) {
		this->init_position();
	}
	else {
		this->position = positions[ai_index];
	}
}


void Bot::decide()
{

	auto pos = this->position;

	if (this->go_left > this->go_right && this->go_left > this->go_straight) {
		this->desicion = LEFT;
	}
	else if (this->go_right > this->go_left && this->go_right > this->go_straight) {
		this->desicion = RIGHT;
	}
	else {
		this->desicion = STRAIGHT;
	}

}

void Bot::bound_check()
{
	const auto& pos = this->position;
	float angle1 = getAngle(this->movement);
	enum { BOUND = 50};
	
	bool non = true;

	//Bound decisions
	if (pos.y <= BOUND && angle1 < 90) {
		this->go_right += 3;
		non = false;
	}
	if (pos.y <= BOUND && angle1 < 180 && angle1 > 90) {
		this->go_left += 3;
		non = false;
	}
	if (pos.x <= BOUND && angle1 <= 180 && angle1 > 90) {
		this->go_right += 3;
		non = false;
	}
	if (pos.x <= BOUND && angle1 <= 270 && angle1 > 180) {
		this->go_left += 3;
		non = false;
	}
	if (pos.x >= WIDTH - BOUND && angle1 <= 360 && angle1 > 270) {
		this->go_right += 3;
		non = false;
	}
	if (pos.y >= HEIGHT - BOUND && angle1 < 270 && angle1 >= 180) {
		this->go_right += 3;
		non = false;
	}
	if (pos.y >= HEIGHT - BOUND && angle1 <= 360 && angle1 > 270) {
		this->go_left += 3;
		non = false;
	}
	if (pos.x >= WIDTH - BOUND && angle1 <= 90) {
		this->go_left += 3;
		non = false;
	}

	if (non) { // no danger left
		this->go_straight += 3;
	}


}

void Bot::initialize()
{
	this->init = true;
}

void Bot::uninitialize()
{
	this->init = false;
}

bool Bot::isInitialized()
{
	return this->init;
}

sf::Vector2f* Bot::get_header_points()
{
	return this->header_points;
}

sf::Vector2f * Bot::get_header2_points()
{
	return this->header2_points;
}

sf::Vector2f * Bot::get_header3_points()
{
	return this->header3_points;
}


