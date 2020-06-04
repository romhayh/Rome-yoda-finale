#pragma once
#include "entity.hpp"

class Bot : public Entity
{
	enum Desicion {
		STRAIGHT, // 0
		LEFT, // 1
		RIGHT // 2
	};
	
	sf::Vector2f header_points[3];
	sf::Vector2f header2_points[2];
	sf::Vector2f header3_points[4];
	int go_left{ 0 };
	int go_right{ 0 };
	int go_straight{ 0 };
	Desicion desicion;

	bool init = false;
public:
	enum {
		RANGE = 11,
		H_RADIUS = 10
	};
public:
	
	Bot();
	Bot(sf::Color&& color, std::string&& name, sf::Vector2f&& position = ORIGIN);
	Bot(const Bot& other);//copy
	Bot& operator= (const Bot& other);
	Bot(Bot&& other);// move
	Bot& operator= (Bot&& other);
	
public:

	void move() override;
	void collision() override;
	bool collision_check() override;
	void init_position() override;
	void decide();
	void bound_check();

public:
	void initialize();
	void uninitialize();
	bool isInitialized();

	sf::Vector2f* get_header_points();
	sf::Vector2f* get_header2_points();
	sf::Vector2f* get_header3_points();

public:
	friend int count_entities_alive();
	friend Entity* highest_score();
	friend int count_bots_init();
};

int count_entities_alive();